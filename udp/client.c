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
    char *line;
    char answer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    char* prefix = "6-";

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
    serverlen = sizeof(serveraddr);

    printf("Type the email to find: \n");
    line = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    fgets(line, BUFFER_SIZE, stdin);

    while (strcmp(line, "exit") != 0) {
      strcat(message, prefix);
      strcat(message, line);
      // Sending the message to the server
      
      n = sendto(sockfd, message, strlen(message), 0, &serveraddr, serverlen);
      if (n < 0) 
        error("ERROR in sendto");
      
      bzero(answer, BUFFER_SIZE);
      // Printing the server's response
      n = recvfrom(sockfd, answer, BUFFER_SIZE, 0, &serveraddr, &serverlen);
      if (n < 0)
        error("ERROR in recvfrom");
      
      printf("%s\n\n", answer);

      bzero(line, BUFFER_SIZE);
      bzero(&message, BUFFER_SIZE);
      fgets(line, BUFFER_SIZE, stdin);
    }

    return 0;
}