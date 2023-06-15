// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DSET_IP_ADDRESS "127.0.0.1"
#define DEST_PORT       8099
#define MAXLINE         1024
#define LOOP_COUNT      3

// Driver code
int main(int argc, char *argv[])
{
    int sockfd;
    uint16_t dest_port = DEST_PORT;
    char *dest_ip = DSET_IP_ADDRESS;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in servaddr;

    if (argc == 3)
    {
        dest_ip = argv[1];
        dest_port = (uint16_t)atoi(argv[2]);
    }

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(dest_port);
    servaddr.sin_addr.s_addr = inet_addr(dest_ip);

    printf("UDP client send to %s:%u\n", dest_ip, dest_port);

    int n, len, cnt = LOOP_COUNT;

    while (cnt--)
    {
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
               (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Hello message sent.\n");
        sleep(1);

#if 1
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *)&servaddr, &len);
        if (n < 0)
        {
            perror("recvfrom() error");
            close(sockfd);
            return 0;
        }

        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
#endif
    }

    close(sockfd);
    return 0;
}