#include "stm32f10x.h"
#include "stdio.h"

#ifndef __USTART__
#define __USTART__

static void NVIC_Configuration(void);

void USART_Config(void);

void Usart_SendByte( USART_TypeDef *pUSARTTx, uint8_t ch);

void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

void USART1_IRQHandler(void);

extern uint8_t aRxBuffer[1024*10];
extern volatile uint8_t RxCounter;
extern volatile uint8_t ReceiveState;

#endif





