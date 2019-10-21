#include "stm32f10x.h"
#include "ustart.h"
#include "delay.h"



int main(void)
{	 
	USART_Config();
	while(1) 
	{	
		delay_ms(1000);
		Usart_SendString(USART1, "in App\n");
	} 
}

