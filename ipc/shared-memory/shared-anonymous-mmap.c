#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
#define MAP_SIZE 268435456
 
int main()
{
    char *addr;
    ssize_t s;
 
    addr = mmap(NULL, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);
    if (addr == MAP_FAILED) {
        fprintf(stderr, "mmap failed\n");
        exit(EXIT_FAILURE);
    }
    memset(addr, 9, MAP_SIZE);
 
    printf("mmap done, memset done, check free output. Press any key to exit...\n");
    getchar();
    printf("exit success.\n");
    exit(EXIT_SUCCESS);
}
