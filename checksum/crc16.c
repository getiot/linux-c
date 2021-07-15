#include <stdio.h>

static unsigned char msg[] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x01};

static unsigned short CRC16(unsigned char *puchMsg, unsigned short usDataLen)
{
    int i, j;
    unsigned short usRegCRC = 0xFFFF;
    
    for (i=0; i<usDataLen; i++)
    {
        usRegCRC ^= *puchMsg++;
        for (j=0; j<8; j++)
        {
            if (usRegCRC & 0x0001)
                usRegCRC = usRegCRC >> 1 ^ 0xA001;
            else
                usRegCRC >>= 1;
        }
    }
    
    return usRegCRC;
}

static unsigned short CRC16_Checksum(unsigned char *puchMsg, unsigned short usDataLen)
{
    unsigned short i, j, crc_reg, check;

    crc_reg = 0xFFFF;

    for (i=0; i<usDataLen; i++)
    {
        crc_reg = (crc_reg >> 8)^puchMsg[i];
        for (j=0; j<8; j++)
        {
	    check = crc_reg & 0x0001;
	    crc_reg >>= 1;
	    if (check == 0x0001)
	    {
		crc_reg ^= 0xA001;
	    }
        }
    }
    
    return crc_reg;
}

int main(void)
{
    unsigned short crc16 = CRC16(msg, sizeof(msg));
    printf("CRC = %02X\n", crc16);
    printf("CRC = %02X\n", CRC16_Checksum(msg, sizeof(msg)));
    return 0;
}
