#include "stm32f10x.h"
#include "ustart.h"
#include "delay.h"
#include "bootloader.h"
#include "ustartx.h"
#include "flash.h"

u8 data[1024];

int main(void)
{	
	USART_Config();
	
	FLASH_ReadByte(ADDR, data, 50);
	for(int i = 0; i < 50; i++){
		Usart_SendByte(USART1, data[i]);
	}
	
	while(1) 
	{	
//		printf("in bootloader\n");
//		fun_jump(JUMP_ADDR);
	} 
}

