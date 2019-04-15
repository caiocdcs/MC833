// Description: A simple TCP server serving a database
// Usage: ./server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "controller.h"

#define PORT 8888
#define MAX_CLIENTS 30
#define BUFFER_SIZE 10

struct sockaddr_in address;

// Array to keep each client socket
int client_socket[MAX_CLIENTS];

// Master socket will assign clients to new ports
int master_socket;

// Set of socket file descritors (fd)
fd_set readfds;

// Size of socket address
int addrlen;

// Keeps highest file descriptor number (need it for the select function)
int max_socket_fd;

// data for getting times
int l = 0;
struct timeval start, stop;
long long int request_times[120];

int sendall(int socket_fd, char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytes_left = *len; // how many we have left to send
    int n = -1;

    // send the size of the message that will be sent
    char *size = malloc(BUFFER_SIZE * sizeof(char));
    sprintf(size, "%d", *len);
    int size_len = strlen(size) + 1;
    n = write(socket_fd, size, size_len);

    usleep(1000);
    free(size);

    // then send the message
    while(total < *len && n != -1) {
        n = send(socket_fd, buf+total, bytes_left, 0);
        if (n == -1) { break; }
        total += n;
        bytes_left -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
}

// Initializes all sockets with blank values
void initializeSockets() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }
}

// Configures master socket to receive incoming connections
void setMasterSocket() {
	// Creating a master socket 
    master_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (master_socket == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set master socket to allow multiple connections
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Setting address with IP (INADDR_ANY) and Port to bind master socket at
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Keeping size of address
	addrlen = sizeof(address);

    // Binding the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Listener on port %d\n", PORT);

    // Specifying maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

// Adds all non-blank sockets to socket reading set
void addValidSocketsToReadSet() {
	// Clearing the socket set 
    FD_ZERO(&readfds);

    // Adding master socket to set 
    FD_SET(master_socket, &readfds);
    max_socket_fd = master_socket;

    // Adding child sockets to set 
    for (int i = 0; i < MAX_CLIENTS; i++) {

        int socket_fd = client_socket[i];

        // If socket descriptor is valid then add to reading set 
        if(socket_fd > 0)
            FD_SET(socket_fd, &readfds);

        // Keeping highest file descriptor number (need it for the select function)
        if(socket_fd > max_socket_fd)
            max_socket_fd = socket_fd;
    }
}

// Waits for an activity on one of the sockets
void waitForActivity() {
    int activity = select(max_socket_fd + 1, &readfds, NULL, NULL, NULL);

    if ((activity < 0) && (errno != EINTR)) {
        printf("-> WARNING: select error");
    }
}

// Reads incoming connectiong on the master socket
void readNewConnections() {
	int new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("New connection, socket file descriptor is %d, IP is: %s , Port: %d\n",
            new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Sending new connection greeting message with commands
    char *message = getCommands();
    int len = strlen(message);

    if (sendall(new_socket, message, &len) == -1) {
        perror("send");
    }

    // Adding new socket to array of sockets
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_socket[i] == 0) {
            client_socket[i] = new_socket;
            printf("Adding %d to list of sockets at index %d\n", new_socket, i);

            break;
        }
    }
}

// Reads IO operations on generic sockets
void readSocketIO(int socket_fd, int pos) {
    // Now read server response with size of the response to be received
    char *message_size = malloc(BUFFER_SIZE * sizeof(char));
    bzero(message_size, BUFFER_SIZE);
    int n = read(socket_fd, message_size, BUFFER_SIZE);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    int size = atoi(message_size);
    char* buffer = malloc(size * sizeof(char));

    free(message_size);

    // Now read server response
    bzero(buffer, size);
    int val_read = read(socket_fd, buffer, size);

    // Getting initial time
    gettimeofday(&start, NULL);

    // Checking if message was for closing (EOF) and also read the incoming message 
    if (val_read == 0) {
        getpeername(socket_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        printf("\nHost disconnected, IP %s, Port %d\n",
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // Closing the socket and marking as 0 in list for reuse 
        close(socket_fd);
        client_socket[pos] = 0;
    } else {
        buffer[size - 1] = '\0';
        char* answer;

        answer = getRequest(buffer);
        int len = strlen(answer);

        // Getting final time
        gettimeofday(&stop, NULL);

        request_times[l] = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);

        // printing processment time
        if (l % 20 == 0) {
            printf("\n");
        }
        printf("%llu\t", request_times[l++]);

    	// Sending answer back to client
    	sendall(socket_fd, answer, &len);
    	free(answer);
    }

    free(buffer);
}

int main(int argc, char *argv[]) {

	initializeSockets();

	// Configuring master socket to read new connections and control other sockets
	setMasterSocket();

    printf("Waiting for connections...\n");
    
    // Accepting incoming connections
    for (;;) {
    	// Adding every valid (not blank) socket to the reading set
        addValidSocketsToReadSet();

        // Waiting for an activity on one of the sockets
        waitForActivity();

        // If master socket is on reading set, then it is an incoming connection 
        if (FD_ISSET(master_socket, &readfds)) {
            readNewConnections();
        }

        // For every socket, if it is on the reading set then read its IO operation
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int socket_fd = client_socket[i];

            if (FD_ISSET(socket_fd, &readfds)) {
                readSocketIO(socket_fd, i);
            }
        }
    }
    
    return 0;
}