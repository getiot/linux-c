#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#define DATA_LEN 64

static void print_timestamp()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("[%ld.%09ld] ", ts.tv_sec, ts.tv_nsec);
}

int open_can_socket(const char *ifname)
{
    int sock;
    struct sockaddr_can addr;
    struct ifreq ifr;

    sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    // 启用 CAN FD 支持
    int enable_canfd = 1;
    if (setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FD_FRAMES,
                   &enable_canfd, sizeof(enable_canfd))) {
        perror("setsockopt CAN_RAW_FD_FRAMES");
        close(sock);
        return -1;
    }

    strcpy(ifr.ifr_name, ifname);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        perror("SIOCGIFINDEX");
        close(sock);
        return -1;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sock);
        return -1;
    }

    return sock;
}

void send_loop(int sock, canid_t can_id)
{
    struct canfd_frame frame;
    memset(&frame, 0, sizeof(frame));

    frame.can_id = can_id;
    frame.len = DATA_LEN;      // 64 bytes
    frame.flags = CANFD_BRS;   // 开启 Bit Rate Switch

    // 填充测试数据
    for (int i = 0; i < DATA_LEN; i++)
        frame.data[i] = i;

    printf("Start sending CAN FD frames...\n");

    while (1) {
        print_timestamp();

        int nbytes = write(sock, &frame, sizeof(frame));
        if (nbytes != sizeof(frame)) {
            perror("write");
        } else {
            printf("Sent 64 bytes (ID=0x%X)\n", can_id);
        }

        usleep(1000000); // 1 秒发一次（方便观察）
    }
}

void recv_loop(int sock)
{
    struct canfd_frame frame;

    printf("Start receiving...\n");

    while (1) {
        int nbytes = read(sock, &frame, sizeof(frame));
        if (nbytes < 0) {
            perror("read");
            continue;
        }

        print_timestamp();
        printf("Received ID=0x%X  len=%d  data=",
               frame.can_id & CAN_EFF_MASK,
               frame.len);

        for (int i = 0; i < frame.len; i++)
            printf("%02X ", frame.data[i]);

        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage:\n");
        printf("  %s <ifname> send <can_id>\n", argv[0]);
        printf("  %s <ifname> recv\n", argv[0]);
        return 1;
    }

    const char *ifname = argv[1];
    const char *mode = argv[2];

    int sock = open_can_socket(ifname);
    if (sock < 0)
        return 1;

    if (strcmp(mode, "send") == 0) {
        if (argc < 4) {
            printf("Need CAN ID\n");
            return 1;
        }
        canid_t can_id = strtol(argv[3], NULL, 0);
        send_loop(sock, can_id);
    } else if (strcmp(mode, "recv") == 0) {
        recv_loop(sock);
    } else {
        printf("Unknown mode\n");
    }

    close(sock);
    return 0;
}