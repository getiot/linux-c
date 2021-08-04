#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

typedef enum {
    LINK_UP,
    LINK_DOWN
} link_status_t;

static int set_ether_status(const char *ethNum, const link_status_t status)
{
    struct ifreq ifr;
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Create socket fails!\n");
        return -1;
    }
    
    strcpy(ifr.ifr_name, ethNum);
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
        printf("ioctl SIOCGIFFLAGS fails!\n");
        close(sockfd);
        return -1;
    }

    if (status == LINK_UP) {
        ifr.ifr_flags |= IFF_UP;
    }
    else if (status == LINK_DOWN) {
        ifr.ifr_flags &= ~IFF_UP;
    }
    
    if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0) {
        printf("ioctl SIOCSIFFLAGS fails!\n");
        close(sockfd);
        return -1;
    }
    
    close(sockfd);
    return 0;
}

int main(int argc, char *argv[])
{
    link_status_t status;
    char *netdev_name;

    if (argc != 3) {
        printf("Usage: %s <netdev> <up|down>\n", argv[0]);
        return -1;
    }

    netdev_name = argv[1];
    
    if (0 == strcmp(argv[2], "up")) {
        status = LINK_UP;
    }
    else if (0 == strcmp(argv[2], "down")) {
        status = LINK_DOWN;
    }
    else {
        printf("Invaild arguments\n");
        return -1;
    }

    set_ether_status(netdev_name, status);

    return 0;
}
