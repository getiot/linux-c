// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    8099
#define MAXLINE 1024

// Driver code
int main(int argc, char *argv[])
{
    int sockfd;
    uint16_t port = PORT;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    if (argc == 2)
    {
        port = (uint16_t)atoi(argv[1]);
    }

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP server established on %u\n", port);

    int len, n;

    len = sizeof(cliaddr); // len is value/result

    while (1)
    {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *)&cliaddr, &len);
        if (n < 0)
        {
            perror("recvfrom() error");
            close(sockfd);
            return 0;
        }

        buffer[n] = '\0';
        printf("Client : %s\n", buffer);

        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM,
               (const struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);
    return 0;
}