#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

char *GetGatewayForInterface(const char* interface, char *gateway, size_t len) 
{
    assert(gateway);

    char cmd [1000] = {0x0};
    char line[256]  = {0x0};

    sprintf(cmd,"route -n | grep %s  | grep 'UG[ \t]' | awk '{print $2}'", interface);
    FILE* fp = popen(cmd, "r");
    if (fp == NULL) {
        return NULL;
    }

    if (NULL == fgets(line, sizeof(line), fp)) {
        return NULL;
    }
    pclose(fp);

    if (line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = '\0';
    }
    
    strncpy(gateway, line, len);
    return gateway;
}

int main(int argc, char *argv[])
{
    char gateway[32] = {0};

    if (argc < 2) {
        printf("Usage: %s <ifname>\n", argv[0]);
        return -1;
    }

    if (NULL == GetGatewayForInterface(argv[1], gateway, sizeof(gateway))) {
        printf("No Gateway for %s\n", argv[1]);
        return -1;
    }

    printf("Gateway: %s\n", gateway);

    return 0;
}