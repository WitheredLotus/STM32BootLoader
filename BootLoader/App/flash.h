
#ifndef __FLASH__
#define __FLASH__

#include "sys.h"
#include "flash.h"

#define ADDR 0x8002000


//��ָ����ַд������
void FLASH_WriteByte(u32 addr , u8 *p , u16 Byte_Num);

//��ָ����ַ��������
void FLASH_ReadByte(u32 addr , u8 *p , u16 Byte_Num);


#endif





