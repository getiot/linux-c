/*
 * gcc -o get_dns get_dns.c -lresolv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>

int main()
{
    res_state res = malloc(sizeof(struct __res_state));
    res_ninit(res);
    int i = 0;
    
    printf("cnt: %d\n", res->nscount);
    for (i = 0; i < res->nscount; i++) /* _res.nscount为找到的域名服务器的数量 */
    {
        struct sockaddr_in addr; /* 域名服务器的地址 */
	memcpy(&addr, &res->nsaddr_list[i], sizeof(addr));
	printf("%s\n", inet_ntoa(addr.sin_addr));
    }
    
    int class = ns_c_in;
    int type = QUERY;
    uint8_t answer[256] = {0};
    
    res_nquery(res, "www.getiot.tech", class, type, answer, sizeof(answer));
    res_nclose(res);
    printf("answer=%u.%u.%u.%u\n", answer[0], answer[1], answer[2], answer[3]); /* answer中为域名解析的结果 */

    return 0;
}
