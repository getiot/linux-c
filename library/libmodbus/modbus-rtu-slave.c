#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "modbus.h" // 引用libmodbus库
 
 
/*
Thegoal of this program is to check all major functions of libmodbus:
-- write_coil
-- read_bits
-- write_coils
-- write_register
-- read_registers
-- write_registers
-- read_registers
All these functions are called with random values on a address range defined by the following defines
*/
#define Loop             1      // 循环次数
#define Server_ID       17      // 从端设备地址
#define ADDRESS_START    0      // 测试寄存器起始地址
#define ADDRESS_END     99      // 测试寄存器结束地址

int main(int argc, char *argv[])
{
    modbus_t *ctx = NULL;

    int nb = 0; // 需要测试的寄存器个数

    uint8_t* tab_rq_bits;       // 用于保存发送或接收的数据（下同）
    uint8_t* tab_rp_bits;

    uint16_t *tab_rq_registers;
    uint16_t *tab_rw_rq_registers;
    uint16_t *tab_rp_registers;
    char *port;

    modbus_mapping_t *mb_mapping;

    if (argc == 2) {
        port = argv[1];
    } else {
        port = "COM5";
    }

    // 创建一个RTU类型的容器
    ctx = modbus_new_rtu(port, 19200, 'N', 8, 1);
 
    // 设置从端地址
    modbus_set_slave(ctx, Server_ID);
 
    // 设置debug模式
    modbus_set_debug(ctx, true);
 
    // RTU 模式下表示打开串口
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s \n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }
 
    // 申请4块内存区用以存放寄存器数据，这里申请500个寄存器地址
    mb_mapping = modbus_mapping_new(500, 500, 500, 500);
    if (mb_mapping == NULL)
    {
        fprintf(stderr, "Error mapping: %s \n",modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    // 循环接收查询帧并回复消息
    for (;;)
    {
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        int rc = 0;
        rc = modbus_receive(ctx, query);//获取查询报文
 
        if (rc >= 0)
        {
            // rc is the qury size
            modbus_reply(ctx, query, rc, mb_mapping); // 回复响应报文
        }
        else
        {
            // connection closed by the client or error
            printf("Connection Closed\n");
        }
    }

    printf("Quit the loop : %s \n", modbus_strerror(errno));
 
 
    // 释放内存
    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);
 
    return 0;
}
