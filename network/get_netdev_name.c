#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define BUFFER_SIZE    512

int main()
{
    int i, num;
    int sockfd;
    struct ifconf ifc;
    unsigned char buf[BUFFER_SIZE];
    struct ifreq *ifr;

    /* 初始化ifconf */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        perror("socket");
        exit(1);
    }

    /* 获取所有接口信息 */
    ioctl(sockfd, SIOCGIFCONF, &ifc);

    /* 接下来获取逐个网卡的名称和IP地址 */
    ifr = (struct ifreq *)buf;
    num = ifc.ifc_len / sizeof(struct ifreq);

    for(i=0; i<num; i++)
    {
        printf("[%-8s] local address: %s\n", ifr->ifr_name, 
               inet_ntoa(((struct sockaddr_in*)&(ifr->ifr_addr))->sin_addr));
        ifr++;
    }

    return 0;
}
