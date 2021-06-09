#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#define SERIAL_PORT  "/dev/ttyUSB0"

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(void)
{
    int fd; /* File descriptor for the port */

    fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        /*
         * Could not open the port.
         */

        //perror("open_port: Unable to open %s - ", SERIAL_PORT);
        perror("open_port: Unable to open serial device - ");
    }
    else
        fcntl(fd, F_SETFL, 0);

    return (fd);
}

int main(void)
{
    open_port();

    return 0;
}
