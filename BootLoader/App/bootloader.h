#ifndef __BOOTLOADER__
#define __BOOTLOADER__


#include "stdint.h"

#define JUMP_ADDR 0x8002000

typedef  void (*iapfun)(void);				//定义一个函数类型的参数.

void fun_jump(uint32_t appxaddr);

#endif


