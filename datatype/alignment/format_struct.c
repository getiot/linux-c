#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
/*
   0               1               2               3
   0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |               Sob              |            PkgLen            |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                            FrameID                            |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |     Version    |                                              |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
    uint16_t sob;
    uint16_t pkgLen;
    uint32_t frameID;
    uint8_t  version;
} DemoHeader;
#pragma pack(pop)

//#pragma pack(push, 1)
/*
   0               1               2               3
   0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |           Distance             |           Azimuth            |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |           Elevation            |   Intensity   |   Reserved1  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |   Reserved2    |                                              |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
    uint16_t distance;
    uint16_t azimuth;
    uint16_t elevation;
    uint8_t  intensity;
    uint16_t reserved;
} DemoUnit;
//#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    DemoUnit units[32];
} DemoBlock;
#pragma pack(pop)

#pragma pack(push, 1)
/*
   0               1               2               3
   0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                              CRC                              |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |       FS1      |      FS2      |      FS3      |      FS4     |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |       FS5      |      FS6      |      FS7      |      FS8     |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |       FS9      |      FS10     |      FS11     |      FS12    |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |       FS13     |      FS14     |      FS15     |      FS16    |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |       FS17     |                                              |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
    uint32_t crc;
    uint8_t  functionSafety[17];
} DemoTail;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    DemoHeader header;
    DemoBlock block;
    DemoTail tail;
} DemoPacket;
#pragma pack(pop)

int main(void)
{
    DemoPacket packet;

    printf("Size of DemoPacket = %lu\n", sizeof(packet));
    printf("Size of DemoPacket.Header = %lu\n", sizeof(packet.header));
    printf("Size of DemoPacket.Block  = %lu\n", sizeof(packet.block));
    printf("Size of DemoPacket.Tail   = %lu\n", sizeof(packet.tail));
    printf("DemoUnit = %lu\n", sizeof(DemoUnit));

    return 0;
}