#ifndef __BOOTLOADER__
#define __BOOTLOADER__


#include "stdint.h"

#define JUMP_ADDR 0x8002000

typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.

void fun_jump(uint32_t appxaddr);

#endif


