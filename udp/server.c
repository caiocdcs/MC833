// Description: A simple UDP server side code,
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "controller.h"
#include <sys/time.h>

#define PORT 8888

#define BUFSIZE 100000

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    int master_socket;
    int clientlen; /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp; 
    char buffer[BUFSIZE];
    char *answer;
    char *hostaddrp; 
    int optval;
    int n;

    // timeval structs to get time delay on requests made (in milliseconds)
    struct timeval start, stop;
    unsigned long long int processing_time;

    master_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (master_socket < 0)
        error("ERROR opening socket");

    optval = 1;
    setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR,
               (const void *)&optval , sizeof(int));

    // Building the server's Internet address
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);

    // bind
    if (bind(master_socket, (struct sockaddr *) &serveraddr,
             sizeof(serveraddr)) < 0)
        error("ERROR on binding");

    // wait for a datagram, then send the response
    clientlen = sizeof(clientaddr);
    for (;;) {

        bzero(buffer, BUFSIZE);
        n = recvfrom(master_socket, buffer, BUFSIZE, 0,
                     (struct sockaddr *) &clientaddr, &clientlen);
        if (n < 0)
            error("ERROR in recvfrom");

        // Getting initial time
        gettimeofday(&start, NULL);

        hostaddrp = inet_ntoa(clientaddr.sin_addr);

        if (hostaddrp == NULL)
            error("ERROR on inet_ntoa\n");

        printf("server received datagram from %s\n", hostaddrp);
        printf("server received %lu/%d bytes: %s\n", strlen(buffer), n, buffer);

        answer = getRequest(buffer);

        // Getting final time
        gettimeofday(&stop, NULL);
        processing_time = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);

        // send back to the client the answer
        n = sendto(master_socket, answer, strlen(answer), 0,
                   (struct sockaddr *) &clientaddr, clientlen);

        if (n < 0)
            error("ERROR in sendto");

        printf("%llu ", processing_time); // time in milliseconds
    }
}
