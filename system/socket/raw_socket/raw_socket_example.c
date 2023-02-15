#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>

int main(int argc, char *argv[])
{
    int sock_r, buflen;

    sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock_r < 0)
    {
        perror("error in socket");
        return -1;
    }

    unsigned char *buffer = (unsigned char *)malloc(65536); // to receive data
    memset(buffer, 0, 65536);
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);

    while (1)
    {
        // Receive a network packet and copy in to buffer
        buflen = recvfrom(sock_r, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_len);
        if (buflen < 0)
        {
            printf("error in reading recvfrom function\n");
            return -1;
        }

        printf("Received %d bytes: %s\n", buflen, buffer);
    }

    return 0;
}