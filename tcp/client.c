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

#define BUFFER_SIZE 12500

char answer[BUFFER_SIZE];
int socket_fd;


void simulateRequests() {
    // Number of requests of each operation
    int num_requests = 1;

    // Getting timeval structs to get time delay on requests made
    struct timeval start, stop;

    // Keeping time array of each request
    long long int request_times[6][num_requests];

    char *course = "course Music\n";
    char *skill = "skill Sacramento\n";
    char *add_experience = "add_experience jane.doe@gmail.com 'Banco de dados'\n";
    char *get_experience = "get_experience jane.doe@gmail.com\n";
    char *all_profiles = "all_profiles\n";
    char *profile = "profile jane.doe@gmail.com\n";

    char *requests[] = {course, skill, add_experience, get_experience, all_profiles, profile};

    int i, j, k = 0;

    // simulating all requests
    for (i = 0; i < 6; i++) {
        char current_request[1030];
        strcpy(current_request, requests[i]);

        for (j = 0; j < num_requests; j++) {
            // Getting initial time
            gettimeofday(&start, NULL);

            // Send message to the server
            int n = write(socket_fd, current_request, strlen(current_request));

            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }

            // Now read server response
            bzero(answer, BUFFER_SIZE);
            n = read(socket_fd, answer, BUFFER_SIZE);

            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }

            // Getting final time
            gettimeofday(&stop, NULL);

            request_times[i][j] = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);

            printf("%s\n-----", answer);
        }
        
    }

    sleep(1);

    // printing times
//    for (i = 0; i < 4; i++) {
//        for (j = 0; j < num_requests; j++) {
//            printf("%llu\t", request_times[i][j]);
//        }
//        printf("\n");
//    }
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

    // Wait for welcome message (handshake)
    while (n == 0) {
        bzero(answer, BUFFER_SIZE);
        n = read(socket_fd, answer, BUFFER_SIZE);
        printf("%s\n", answer);
    }

    // Now ask for a message from the user, this message will be read by server
    simulateRequests();

    sleep(5);

    return 0;
}