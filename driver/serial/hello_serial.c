/*refer to 
* http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
* http://www.tldp.org/HOWTO/Serial-Programming-HOWTO/x115.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h> /*termio.h for serial IO api*/

#include <pthread.h> /* POSIX Threads */

#define MAX_STR_LEN 256

/*
 * The values for speed are 
 * B115200, B230400, B9600, B19200, B38400, B57600, B1200, B2400, B4800, etc
 * 
 *  The values for parity are 0 (meaning no parity), 
 * PARENB|PARODD (enable parity and use odd), 
 * PARENB (enable parity and use even), 
 * PARENB|PARODD|CMSPAR (mark parity), 
 * and PARENB|CMSPAR (space parity).
 * */

/*
 * if waitTime  < 0, it is blockmode
 *  waitTime in unit of 100 millisec : 20 -> 2 seconds 
 */

int SetInterfaceAttribs(int fd, int speed, int parity, int waitTime)
{
    int isBlockingMode;
    struct termios tty;

    isBlockingMode = 0;
    if (waitTime < 0 || waitTime > 255)
        isBlockingMode = 1;

    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0) /* save current serial port settings */
    {
        printf("__LINE__ = %d, error %s\n", __LINE__, strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;                                 // disable break processing
    tty.c_lflag = 0;                                        // no signaling chars, no echo,
                                                            // no canonical processing
    tty.c_oflag = 0;                                        // no remapping, no delays
    tty.c_cc[VMIN] = (1 == isBlockingMode) ? 1 : 0;         // read doesn't block
    tty.c_cc[VTIME] = (1 == isBlockingMode) ? 0 : waitTime; // in unit of 100 milli-sec for set timeout value

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
                                       // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        printf("__LINE__ = %d, error %s\n", __LINE__, strerror(errno));
        return -1;
    }
    return 0;
} /*SetInterfaceAttribs*/

void *sendThread(void *parameters)
{
    char sendBuff[MAX_STR_LEN];

    memset(&sendBuff[0], 0, MAX_STR_LEN);
    snprintf(&sendBuff[0], MAX_STR_LEN, "hello!");

    int fd;

    fd = *((int *)parameters);

    while (1)
    {
        write(fd, &sendBuff[0], strlen(&sendBuff[0]));

        // sleep enough to transmit the length plus receive 25:
        // approx 100 uS per char transmit
        usleep((strlen(&sendBuff[0]) + 25) * 100);

        usleep(500 * 1000);
    } /*while*/

    pthread_exit(0);
} /*sendThread */

void *readThread(void *parameters)
{
    char readBuff[MAX_STR_LEN];

    int fd;

    fd = *((int *)parameters);

    while (1)
    {
        ssize_t len;

        memset(&readBuff[0], 0, MAX_STR_LEN);

        len = read(fd, &readBuff[0], MAX_STR_LEN);

        if (-1 == len)
        {
            switch (errno)
            {
            case EAGAIN:
                printf("__FUNCTION__ = %s, __LINE__ = %d\n", __FUNCTION__, __LINE__);
                usleep(5 * 1000);
                continue;
                break;

            default:
                printf("__FUNCTION__ = %s, __LINE__ = %d\n", __FUNCTION__, __LINE__);
                pthread_exit(0);
                break;
            }
        }

        if (0 == len)
        {
            printf("devic is lost!\n"); /*device maybe be unplugged*/
            exit(0);
        }

        // sleep enough to transmit the length plus receive 25:
        // approx 100 uS per char transmit
        usleep((len + 25) * 100);
        printf("len = %d\n", (int)len);

        int i;

        for (i = 0; i < len; i++)
            printf("%c(%d %#x)\t", readBuff[i], readBuff[i], readBuff[i]);

        printf("\n");
    } /*while*/

    pthread_exit(0);
} /*readThread */

int main(int argc, char *argv[])
{
    int fd, c, res;
    struct termios oldtio, newtio;
    char buf[MAX_STR_LEN];
    int k;
    char deviceName[MAX_STR_LEN];

    memset(&deviceName[0], 0, MAX_STR_LEN);
    snprintf(&deviceName[0], MAX_STR_LEN, "/dev/ttyUSB0");

    k = 1;
    while (argc > k)
    {
        if (0 == strncmp(argv[k], "-d", MAX_STR_LEN))
        {
            if (k + 1 < argc)
            {
                snprintf(&deviceName[0], MAX_STR_LEN, "%s", argv[k + 1]);
            }
            else
            {
                printf("error : -d should be follow a device!\n");
                return 0;
            }
        }
        k++;
    }

    printf("__FUNCTION__ = %s, __LINE__ = %d\n", __FUNCTION__, __LINE__);

    //non-blocking mode
    //fd = open(&deviceName[0], O_RDWR | O_NOCTTY |O_NONBLOCK| O_NDELAY);

    fd = open(&deviceName[0], O_RDWR | O_NOCTTY);
    if (0 > fd)
    {
        perror(&deviceName[0]);
        exit(-1);
    }

    SetInterfaceAttribs(fd, B57600, 0, 20); /* set speed to 57600 bps, 8n1 (no parity), timeout 2 secs*/

    pthread_t readThread_t, sendThread_t; /* thread variables */

    pthread_create(&readThread_t, NULL, (void *)readThread, (void *)&fd);
    pthread_create(&sendThread_t, NULL, (void *)sendThread, (void *)&fd);

    pthread_join(readThread_t, NULL);
    pthread_join(sendThread_t, NULL);

    close(fd);

    return 0;
} /*main*/
