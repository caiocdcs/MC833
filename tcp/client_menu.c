// Description: A simple TCP client
// Usage: ./client <host> <port>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <math.h>

#include <string.h>

#define BUFFER_SIZE 10

int socket_fd;

int sendall(int socket_fd, char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytes_left = *len; // how many we have left to send
    int n = -1;

    // send the size of the message that will be sent
    char *size = malloc(BUFFER_SIZE * sizeof(char));
    sprintf(size, "%d", *len);
    int size_len = strlen(size);
    n = write(socket_fd, size, size_len);

    usleep(10000);
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

void do_user_commands() {
    char line[1030];
    bzero(line, 1030);
    fgets(line, sizeof(line), stdin);

    while (strcmp(line, "exit") != 0) {
        int len = strlen(line);
        // Send message to the server
        int n = sendall(socket_fd, line, &len);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        // Now read server response with size of the response to be received
        char *message_size = malloc(BUFFER_SIZE * sizeof(char));
        bzero(message_size, BUFFER_SIZE);
        n = read(socket_fd, message_size, BUFFER_SIZE);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        int size = atoi(message_size) + 1;
        char* answer = malloc(size * sizeof(char));

        free(message_size);

        // Now read server response
        bzero(answer, size);
        n = read(socket_fd, answer, size);
        //answer[size-1] = '\0';

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("%s\n\n", answer);
        fflush(stdin);

        bzero(line, 1030);
        fgets(line, sizeof(line), stdin);

        free(answer);
    }
}



int main(int argc, char *argv[]) {
    int portno, n = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    // Create a socket point
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Try to find host
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    // Getting server address (IP and Port)
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Now connect to the server
    if (connect(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    sleep(2);

    // Wait for welcome message
    while (n == 0) {
        // Now read the size of the message to be received
        char *message_size = malloc(BUFFER_SIZE * sizeof(char));
        bzero(message_size, BUFFER_SIZE);
        n = read(socket_fd, message_size, BUFFER_SIZE);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        int size = atoi(message_size) + 1;
        char* answer = malloc(size * sizeof(char));

        free(message_size);

        bzero(answer, BUFFER_SIZE);
        n = read(socket_fd, answer, size);
        answer[size-1] = '\0';
        printf("%s\n", answer);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        free(answer);
    }

    do_user_commands();

    sleep(5);

    return 0;
}