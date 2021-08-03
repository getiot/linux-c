#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/ethtool.h>
#include <linux/sockios.h>
#include <stdint.h>

/**
 * This function will get netdev status using SIOCGMIIPHY and SIOCGMIIREG command.
 *
 * @param skfd   the socket id
 * @param ifname the device name of netdev
 *
 * @return return 0 while link up, 
 *         return 1 while link down, 
 *         return 2 while error.
 */
int detect_mii(int skfd, char *ifname)
{
    struct ifreq ifr;
    uint16_t *data, mii_val;
    unsigned phy_id;

    /* Get the vitals from the interface. */
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);

    if (ioctl(skfd, SIOCGMIIPHY, &ifr) < 0) {
        fprintf(stderr, "SIOCGMIIPHY on %s failed: %s\n", ifname, strerror(errno));
        return 2;
    }

    data = (uint16_t *)(&ifr.ifr_data);
    phy_id = data[0];
    data[1] = 1;

    if (ioctl(skfd, SIOCGMIIREG, &ifr) < 0) {
        fprintf(stderr, "SIOCGMIIREG on %s failed: %s\n", ifr.ifr_name, strerror(errno));
        return 2;
    }

    mii_val = data[3];
    return(((mii_val & 0x0016) == 0x0004) ? 0 : 1);
}

/**
 * This function will get netdev status using SIOCETHTOOL command.
 *
 * @param skfd   the socket id
 * @param ifname the device name of netdev
 *
 * @return return 0 while link up, 
 *         return 1 while link down, 
 *         return 2 while error.
 */
int detect_ethtool(int skfd, char *ifname)
{
    struct ifreq ifr; /* ifreq里包含了接口的所有信息，比如接口名，地址等等 */
    struct ethtool_value edata;

    memset(&ifr, 0, sizeof(ifr));
    edata.cmd = ETHTOOL_GLINK;

    /* 设置要查询的网卡接口名称 */
    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name)-1);
    ifr.ifr_data = (char *) &edata;

    if (ioctl(skfd, SIOCETHTOOL, &ifr) == -1) {
        printf("ETHTOOL_GLINK failed: %s\n", strerror(errno));
        return 2;
    }

    return (edata.data ? 0 : 1);
}

int main(int argc, char *argv[])
{
    int skfd = -1;
    int ret;

    if (argc != 3) {
        printf("Usage: %s <netdev> <t|m>\n", argv[0]);
        printf("       t - SIOCETHTOOL\n");
        printf("       m - SIOCGMIIPHY\n");
        return 0;
    }

    if (( skfd = socket( AF_INET, SOCK_DGRAM, 0 ) ) < 0 )
    {
        printf("socket error\n");
        exit(-1);
    }

    /* 这里使用两种方式来获取网卡的状态 */
    if (argv[2][0] == 't') {
        /* 使用SIOCETHTOOL方式获取 */
        ret = detect_ethtool(skfd, argv[1]);
    }
    else if (argv[2][0] == 'm') {
        /* 使用 SIOCGMIIPHY 方式获取，即先获取指定 phy 的地址，然后读指定 phy 寄存器的值 */
        ret = detect_mii(skfd, argv[1]);
    }
    else {
        printf("Invaild arguments\n");
        close(skfd);
        return -1;
    }

    if (ret == 0) {
        printf("%s is link up\n", argv[1]);
    }
    else if (ret == 1) {
        printf("%s is link down\n", argv[1]);
    }
    else {
        printf("Can not detect status\n");
    }
    
    close(skfd);
    return 0;
}
