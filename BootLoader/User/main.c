#include "stm32f10x.h"
#include "ustart.h"
#include "delay.h"
#include "bootloader.h"


int main(void)
{	
	USART_Config();
	while(1) 
	{	
		printf("in bootloader\n");
		fun_jump(JUMP_ADDR);
	} 
}

