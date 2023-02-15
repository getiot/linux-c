#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/serial.h>

/* Include definition for RS485 ioctls: TIOCGRS485 and TIOCSRS485 */
#include <sys/ioctl.h>

int main(void)
{
	/* Open your specific device (e.g., /dev/mydevice): */
	int fd = open ("/dev/mydevice", O_RDWR);
	if (fd < 0) {
		/* Error handling. See errno. */
	}

	struct serial_rs485 rs485conf;

	/* Enable RS485 mode: */
	rs485conf.flags |= SER_RS485_ENABLED;

	/* Set logical level for RTS pin equal to 1 when sending: */
	rs485conf.flags |= SER_RS485_RTS_ON_SEND;
	/* or, set logical level for RTS pin equal to 0 when sending: */
	rs485conf.flags &= ~(SER_RS485_RTS_ON_SEND);

	/* Set logical level for RTS pin equal to 1 after sending: */
	rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
	/* or, set logical level for RTS pin equal to 0 after sending: */
	rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);

	/* Set rts delay before send, if needed: */
	rs485conf.delay_rts_before_send = 0;

	/* Set rts delay after send, if needed: */
	rs485conf.delay_rts_after_send = 0;

	/* Set this flag if you want to receive data even while sending data */
	rs485conf.flags |= SER_RS485_RX_DURING_TX;

	if (ioctl (fd, TIOCSRS485, &rs485conf) < 0) {
		/* Error handling. See errno. */
	}

	/* Use read() and write() syscalls here... */

	/* Close the device when finished: */
	if (close (fd) < 0) {
		/* Error handling. See errno. */
	}
}