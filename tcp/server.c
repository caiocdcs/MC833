    
// Description: A simple TCP server side code, which echos back the received message.
// Handle multiple socket connections with select and fd_set on Linux.

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

// Defining server's port number
#define PORT 8888
// Defining maximum number of simultaneous clients
#define MAX_CLIENTS 30
// Data buffer of 1k
#define BUFFER_SIZE 1025

// Address of the server with IP and Port
struct sockaddr_in address;
// Array to keep each client socket (struct declared on "server.h")
int client_socket[MAX_CLIENTS];

// Master socket will assign clients to new ports
int master_socket;
// Set of socket file descritors (fd)
fd_set readfds;
// Size of socket address
int addrlen;
// Keeps highest file descriptor number (need it for the select function)
int max_socket_fd;

// Initializes all sockets with blank values
void initializeSockets() {
    // Initializing all client_socket[] to 0 so not checked 
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
        
        // Socket descriptor
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
    // Timeout is NULL, so wait indefinitely
    int activity = select(max_socket_fd + 1, &readfds, NULL, NULL, NULL);

    // Verifying error on socket activity
    if ((activity < 0) && (errno != EINTR)) {
        printf("-> WARNING: select error");
    }
}

// Reads incoming connectiong on the master socket
void readIncomingConnections() {
	int new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Informing of new user connection
    printf("New connection, socket file descriptor is %d, IP is: %s , Port: %d\n",
            new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Sending new connection greeting message
    char *message = "You are connected to the people server.\n";

    if (write(new_socket, message, strlen(message)) != strlen(message)) {
        perror("send");
    }

    printf("Welcome message sent successfully\n");

    // Adding new socket to array of sockets
    for (int i = 0; i < MAX_CLIENTS; i++) {
        // Assigning new socket to some empty position
        if (client_socket[i] == 0) {
            client_socket[i] = new_socket;
            printf("Adding %d to list of sockets at index %d\n", new_socket, i);

            break;
        }
    }
}

// Reads IO operations on generic sockets
void readSocketIO(int socket_fd, int pos) {
    char buffer[BUFFER_SIZE];
    int valread = read(socket_fd, buffer, BUFFER_SIZE-1);
    // Checking if message was for closing (EOF) and also read the incoming message 
    if (valread == 0) {
        // Somebody disconnected, get his details and print 
        getpeername(socket_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        printf("Host disconnected, IP %s, Port %d\n",
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // Closing the socket and marking as 0 in list for reuse 
        close(socket_fd);
        client_socket[pos] = 0;
    }

    // Getting and echoing back the message that came in
    else {
        // Setting the string terminating NULL byte on the end of the data read
        buffer[valread] = '\0';
        char* answer;

        answer = getRequest(buffer);

    	// Echoing answer back to client
    	write(socket_fd, answer, strlen(answer));
        free(answer);
    }
}

// Let the magic begin...
int main(int argc, char *argv[]) {

	// Initializing all sockets with blank
	initializeSockets();

	// Configuring master socket to read new connections and control other sockets
	setMasterSocket();

    printf("Waiting for connections...\n");


    // Adding every valid (not blank) socket to the reading set
    addValidSocketsToReadSet();

    // Waiting for an activity on one of the sockets
    waitForActivity();

    // If master socket is on reading set, then it is an incoming connection 
    if (FD_ISSET(master_socket, &readfds)) {
        readIncomingConnections();
    }

    // For every socket, if it is on the reading set then read its IO operation
    for (int i = 0; i < MAX_CLIENTS; i++) {
        int socket_fd = client_socket[i];
        if (FD_ISSET(socket_fd, &readfds)) {
            readSocketIO(socket_fd, i);
        }
    }

    // reading requests and calculating processment time
    
    // Accepting incoming connections
    for (;;) {
    	// Adding every valid (not blank) socket to the reading set
        addValidSocketsToReadSet();

        // Waiting for an activity on one of the sockets
        waitForActivity();

        // If master socket is on reading set, then it is an incoming connection 
        if (FD_ISSET(master_socket, &readfds)) {
            readIncomingConnections();
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