#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MEM_SIZE  64
#define TEST_MSG  "Hello, GetIoT.tech!"

int main()
{
    int fd;
    char *data;
    const char *filename = "/tmp/shared_memory";

    /* 创建一个文件，用于共享内存 */
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    /* 设置文件大小 */
    if (ftruncate(fd, MEM_SIZE) < 0) {
        perror("ftruncate");
        exit(1);
    }
    /* 映射到内存中 */
    data = (char *) mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    /* 关闭文件描述符，不再需要 */
    close(fd);

    /* 使用共享内存 */
    memcpy(data, TEST_MSG, sizeof(TEST_MSG));
    printf("%s\n", (char *)data);

    /* 解除映射 */
    if (munmap(data, MEM_SIZE) < 0) {
        perror("munmap");
        exit(1);
    }

    /* 删除文件 */
    if (unlink(filename) < 0) {
        perror("unlink");
        exit(1);
    }

    return 0;
}
