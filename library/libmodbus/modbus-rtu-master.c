#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "modbus.h"	// 引用libmodbus库
 
 
/* The goal of this program is to check all major functions of 
libmodbus:
- write_coil
- read_bits
- write_coils
- write_register
- read_registers
- write_registers
- read_registers

All these functions are called with random values on a address 
range defined by the following defines
*/

#define Loop             1        // 循环次数
#define Server_ID       17        // 从端设备地址
#define ADDRESS_START    0        // 测试寄存器起始地址
#define ADDRESS_END     99        // 测试寄存器结束地址
 
int main(int argc, char *argv[])
{
	// printf("%c", 0b01000001); // A
	modbus_t *ctx = nullptr;
 
	int nb = 0; // 需要测试的寄存器个数
 
	uint8_t* tab_rq_bits;		// 用于保存发送或接收的数据（下同）
	uint8_t* tab_rp_bits;
 
	uint16_t *tab_rq_registers;
	uint16_t *tab_rw_rq_registers;
	uint16_t *tab_rp_registers;
 
	// RTU 
	// 创建一个RTU类型的容器
	ctx = modbus_new_rtu("COM4", 19200, 'N', 8, 1);
 
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
 
	/*Allocate and initialize the different memory space */
	// 计算需要测试的寄存器个数
	nb = ADDRESS_END - ADDRESS_START;
 
 
	// 以下申请内存块，泳衣保存发送和接收各数据
	tab_rq_bits = (uint8_t*)malloc(nb * sizeof(uint8_t));
	memset(tab_rq_bits, 0, nb*sizeof(uint8_t));
 
	tab_rp_bits = (uint8_t*)malloc(nb * sizeof(uint8_t));
	memset(tab_rp_bits, 0, nb*sizeof(uint8_t));
 
	tab_rq_registers = (uint16_t*)malloc(nb * sizeof(uint16_t));
	memset(tab_rq_registers, 0, nb*sizeof(uint16_t));
 
	tab_rw_rq_registers = (uint16_t*)malloc(nb * sizeof(uint16_t));
	memset(tab_rw_rq_registers, 0, nb*sizeof(uint16_t));
 
	tab_rp_registers = (uint16_t*)malloc(nb * sizeof(uint16_t));
	memset(tab_rp_registers, 0, nb*sizeof(uint16_t));
 
 
	int nb_loop = 0, nb_fail = 0, addr = 0, rc = 0;
 
	while (nb_loop++ < Loop)
	{
		// 从起始地址开始顺序测试
		for (addr = ADDRESS_START; addr < ADDRESS_END; addr++)
		{
			Sleep(500);
 
			int i = 0;
 
			// 生成随机数用于测试
			for (i = 0; i < nb; i++)
			{
				tab_rq_registers[i] = (uint16_t)(65535.0 * rand() / (RAND_MAX + 1.0));
				tab_rw_rq_registers[i] = ~tab_rq_registers[i];
				tab_rq_bits[i] = tab_rq_registers[i] % 2;
			}
			nb = ADDRESS_END - addr;
 
 
			// 测试线圈寄存器的单个读写
			rc = modbus_write_bit(ctx, addr, tab_rq_bits[0]); // 写线圈寄存器
			if (rc != 1)
			{
				printf("ERROR modbus_write_bit (%d)\n", rc);
				printf("Address = %d,value = %d \n", addr, tab_rq_bits[0]);
				nb_fail++;
			}
			else
			{
				// 写入之后，再读取并比较
				rc = modbus_read_bits(ctx, addr, 1, tab_rp_bits);
				if (rc != 1 || tab_rq_bits[0] != tab_rp_bits[0])
				{
					printf("ERROR modbus_read_bits single(%d)\n");
					printf("address = %d\n", addr);
					nb_fail++;
				}
			}
 
			// 测试线圈寄存器的批量读写
			rc = modbus_write_bits(ctx, addr, nb, tab_rq_bits);
			if (rc != nb)
			{
				printf("ERROR modbus_write_bits (%d)\n", rc);
				printf("Address = %d,nb = %d\n", addr, nb);
				nb_fail++;
			}
			else
			{
				// 写入之后，再读取并比较
				rc = modbus_read_bits(ctx, addr, nb, tab_rp_bits);
				if (rc != nb)
				{
					printf("ERROR modbus_read_bits \n");
					printf("address = %d,nb = %d\n", addr, nb);
					nb_fail++;
				}
				else
				{
					// 进行比较
					for (i = 0; i < nb; i++)
					{
						if (tab_rp_bits[i] != tab_rq_bits[i])  // 待完善
						{
							printf("ERROR modbus_read_bits (%d)\n", rc);
							printf("Address = %d, Val = %d(0x%x) != %d (0x%x)\n",
								addr, tab_rq_bits[i], tab_rq_bits[i],
								tab_rp_bits[i], tab_rp_bits[i]);
							nb_fail++;
						}
					}
				}
			}
 
 
			// 测试保持寄存器的单个读写
			rc = modbus_write_register(ctx, addr, tab_rq_registers[0]);
			if (rc != 1)
			{
				printf("ERROR modbus_read_bits (%d)\n", rc);
				printf("Address = %d, Val = %d(0x%x)\n",
					addr, tab_rq_registers[0], tab_rq_registers[0]);
				nb_fail++;
			}
			else
			{
				// 写入之后进行读取
				rc = modbus_read_registers(ctx, addr, 1, tab_rp_registers);
				if (rc != 1)
				{
					printf("ERROR modbus_read_registers (%d)\n", rc);
					printf("Address = %d\n", addr);
					nb_fail++;
				}
				else
				{
					// 读取后进行比较
					if (tab_rq_registers[0] != tab_rp_registers[0])  // 待完善
					{
						printf("ERROR modbus_read_registers (%d)\n", rc);
						printf("Address = %d, Val = %d(0x%x) != %d (0x%x)\n",
							addr, tab_rq_registers[0], tab_rq_registers[0],
							tab_rp_registers[0], tab_rp_registers[0]);
						nb_fail++;
					}
				}
			}
 
 
			// 测试线圈寄存器的批量读写
			rc = modbus_write_registers(ctx, addr, nb, tab_rq_registers);
			if (rc != nb)
			{
				printf("ERROR modbus_write_bits (%d)\n", rc);
				printf("Address = %d, nb = %d \n",
					addr, nb);
				nb_fail++;
			}
			else
			{
				// 进行读取测试
				rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
				if (rc != nb)
				{
					printf("ERROR modbus_read_registers (%d)\n", rc);
					printf("Address = %d\n", addr);
					nb_fail++;
				}
				else
				{
					for (i = 0; i < nb; i++)
					{
						// 读取后进行比较 
						if (tab_rq_registers[i] != tab_rp_registers[i]) 
						{
							printf("ERROR modbus_read_registers (%d)\n", rc);
							printf("Address = %d, Val = %d(0x%x) != %d (0x%x)\n",
								addr, tab_rq_registers[0], tab_rq_registers[0],
								tab_rp_registers[0], tab_rp_registers[0]);
							nb_fail++;
						}
					}
 
				}
			}
 
			// 功能码 23 （0x17） 读写多个寄存器的测试
			rc = modbus_write_and_read_registers(ctx, 
				addr, nb, tab_rw_rq_registers,
				addr, nb, tab_rp_registers);
 
			if (rc != nb)
			{
				printf("ERROR modbus_read_ad_write_registers (%d)\n", rc);
				printf("Address = %d,nb = %d\n", addr, nb);
				nb_fail++;
			}
			else
			{
				// 读取并比较
				for (i = 0; i < nb; i++)
				{
					if (tab_rp_registers[i] < tab_rw_rq_registers[i])
					{
						printf("ERROR modbus_read_and_write_registers READ\n");
						printf("Address = %d,value %d (0x%X) != %d (0x%X)\n",
							addr, tab_rp_registers[i], tab_rw_rq_registers[i],
							tab_rp_registers[i, tab_rw_rq_registers[i]]);
						nb_fail++;
					}
				}
 
				rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
				if (rc != nb)
				{
					printf("ERROR modbus_read_registers (%d) \n", rc);
					printf("Address = %d,nb = %d\n", addr, nb);
				}
				else
				{
					for (i = 0; i < nb; i++)
					{
						if (tab_rw_rq_registers[i] != tab_rp_registers[i])
						{
							printf("ERROR modbus_read_and_write_registers \n");
							printf("Address = %d,value %d (0x%X) != %d (0x%X)\n",
								addr, tab_rw_rq_registers[i], tab_rw_rq_registers[i],
								tab_rp_registers[i], tab_rp_registers[i]);
							nb_fail++;
						}
					}
				}
			}
		}
 
		printf("Test: ");
		if (nb_fail)
		{
			printf("%d FAILS\n",nb_fail);
		}
		else
		{
			printf("SUCCESS\n");
		}
	}
 
	// FREE the memory
	free(tab_rq_bits);
	free(tab_rp_bits);
	free(tab_rq_registers);
	free(tab_rp_registers);
	free(tab_rw_rq_registers);
 
	// close the connection
	modbus_close(ctx);
	modbus_free(ctx);
 
	return 0;
}
