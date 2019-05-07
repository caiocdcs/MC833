/* 
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h>

#define BUFFER_SIZE 100000

void calculateTimes(struct sockaddr_in serveraddr, int sockfd) {
    int num_requests = 20;
    int j, n;
    int serverlen;
    // timeval structs to get time delay on requests made (in milliseconds)
    struct timeval start, stop;
    long long int request_times[num_requests];
    char answer[BUFFER_SIZE];

    char *message = "6-jane.doe@gmail.com";

    // Simulating all requests
        char current_request[BUFFER_SIZE];
        strcpy(current_request, message);

        for (j = 0; j < num_requests; j++) {
            // Getting initial time
            gettimeofday(&start, NULL);

            // Send message to the server
		    serverlen = sizeof(serveraddr);
            n = sendto(sockfd, current_request, strlen(current_request), 0, &serveraddr, serverlen);
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }

            // Now read server response
            bzero(answer, BUFFER_SIZE);
    
		    // Printing the server's reply
		    n = recvfrom(sockfd, answer, BUFFER_SIZE, 0, &serveraddr, &serverlen);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }

            // Getting final time
            gettimeofday(&stop, NULL);

            request_times[j] = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
        }

    sleep(1);

    // printing times
    for (j = 0; j < num_requests; j++) {
        printf("%llu\t", request_times[j]);
    }
}


void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;

    // Checking command line arguments
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    // Building the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serveraddr.sin_addr.s_addr,
          server->h_length);
    serveraddr.sin_port = htons(portno);

    calculateTimes(serveraddr, sockfd);

    return 0;
}