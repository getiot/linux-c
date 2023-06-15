#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PORT 8099

int main() {
    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket() error");
        exit(1);
    }

    // 监听指定端口
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind() error");
        exit(1);
    }

    // 开始接收数据
    char buf[BUF_SIZE];
    while (1) {
        memset(buf, 0, BUF_SIZE);
        int len = recv(sockfd, buf, BUF_SIZE, 0);
        if (len < 0) {
            perror("recv() error");
            exit(1);
        }

        printf("Received UDP packet with length %d bytes.\n", len);
        printf("Data: %s\n", buf);
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}