
#ifndef __FLASH__
#define __FLASH__

#include "sys.h"
#include "flash.h"

#define ADDR 0x8002000


//在指定地址写入数组
void FLASH_WriteByte(u32 addr , u8 *p , u16 Byte_Num);

//在指定地址读出数组
void FLASH_ReadByte(u32 addr , u8 *p , u16 Byte_Num);


#endif





