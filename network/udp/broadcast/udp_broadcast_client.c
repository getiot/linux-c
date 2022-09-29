#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define IP_FOUND "IP_FOUND"
#define IP_FOUND_ACK "IP_FOUND_ACK"
#define PORT 9999

int main()
{
    int sock;
    int yes = 1;
    struct sockaddr_in broadcast_addr;
    struct sockaddr_in server_addr;
    int addr_len;
    int count;
    int ret;
    fd_set readfd;
    char buffer[1024];
    int i;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("sock error");
        return -1;
    }
    ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));
    if (ret == -1)
    {
        perror("setsockopt error");
        return 0;
    }

    addr_len = sizeof(struct sockaddr_in);

    memset((void *)&broadcast_addr, 0, addr_len);
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    broadcast_addr.sin_port = htons(PORT);

    for (i = 0; i < 3; i++)
    {
        ret = sendto(sock, IP_FOUND, strlen(IP_FOUND), 0, (struct sockaddr *)&broadcast_addr, addr_len);

        FD_ZERO(&readfd);
        FD_SET(sock, &readfd);

        ret = select(sock + 1, &readfd, NULL, NULL, NULL);

        if (ret > 0)
        {
            if (FD_ISSET(sock, &readfd))
            {
                count = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&server_addr, &addr_len);
                printf("recvmsg is %s\n", buffer);
                if (strstr(buffer, IP_FOUND_ACK))
                {
                    printf("found server IP is %s, Port is %d\n", inet_ntoa(server_addr.sin_addr), htons(server_addr.sin_port));
                }
            }
        }
    }
}
