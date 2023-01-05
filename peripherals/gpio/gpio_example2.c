#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>

#define GPIO1_B3  43 /* GPIO1_B3 = 1*32+8+3 = 43 */
#define RK_PB3    11

#define msleep(t) usleep((t)*1000)

int main(int argc, char const *argv[])
{
    struct gpiod_chip *gpiochip1;
    struct gpiod_line *pin;
    struct gpiod_line_request_config config;
    int req;

    /* 打开 GPIO 控制器 */
    gpiochip1 = gpiod_chip_open("/dev/gpiochip1");
    if (!gpiochip1) {
        fprintf(stderr, "gpio chip open error.\n");
        return -1;
    }

    /* 获取 GPIO1_B3 引脚 */
    pin = gpiod_chip_get_line(gpiochip1, RK_PB3);

    if (!pin) {
        fprintf(stderr, "gpio get line error.\n");
        gpiod_chip_close(gpiochip1);
        return -1;
    }

    /* 配置引脚  输出模式 name为“bilik” 初始电平为low*/
    req = gpiod_line_request_output(pin, "blink", 0);
    if (req) {
        fprintf(stderr, "gpio request error.\n");
        return -1;
    }

    while (1) {
        /* 设置引脚电平 */
        gpiod_line_set_value(pin, 1);
        printf("set pin to 0\n");
        msleep(500);
        gpiod_line_set_value(pin, 0);
        printf("set pin to 1\n");
        msleep(500);
    }

    return 0;
}
