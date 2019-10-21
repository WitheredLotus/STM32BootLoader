#include "ustart.h"
#include "flash.h"


uint8_t aRxBuffer[1024*10]={0x00};
volatile uint8_t RxCounter=0;
volatile uint8_t ReceiveState=0;

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//嵌套中断控制器组选择
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//配置USART 为中断源
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	
	//抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	
	//子优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	//初始化配置NVIC
	NVIC_Init(&NVIC_InitStructure);
	
	
}


void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//打开串口外设时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);
	
	//将USART Tx的GPIO配置为推婉复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//配置串口的工作模式
	//配置波特率
	USART_InitStructure.USART_BaudRate = 115200;
	
	//配置帧数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	//配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	
	//配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	
	//配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	//配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	//完成串口初始化配置
	USART_Init(USART1, &USART_InitStructure);
	
	//串口中断优先级配置
	NVIC_Configuration();
	
	//使能串口接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//使能IDLE空闲中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	

	USART_ClearFlag(USART1,USART_FLAG_TC);
	
	//使能串口
	USART_Cmd(USART1, ENABLE);	
}

void Usart_SendByte( USART_TypeDef *pUSARTx, uint8_t ch)
{
	//发送一个字节数据到USART
	USART_SendData(pUSARTx,ch);
	
	//等待发送数据寄存器为空
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
}

void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	
	unsigned int k = 0;
	
	do
	{
		Usart_SendByte( pUSARTx, *(str + k) );
		k++;
	}while( *(str + k) != '\0' );
	
	while( USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET);
		
}


void USART1_IRQHandler(void)
{	
	uint8_t Clear=Clear;//这种定义方法，用来消除编译器的"没有用到"提醒
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // 如果接收到1个字节
	{ 	
		aRxBuffer[RxCounter++] = USART1->DR;// 把接收到的字节保存，数组地址加1
	} 
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)// 如果接收到1帧数据
	{
		Clear=USART1->SR;// 读SR寄存器
		Clear=USART1->DR;// 读DR寄存器(先读SR再读DR，就是为了清除IDLE中断)
		ReceiveState=1;// 标记接收到了1帧数据
		
		for(int i = 0; i < RxCounter; i++){
			Usart_SendByte(USART1, aRxBuffer[i]);
		}
		if(aRxBuffer[RxCounter-2] == 'A' && aRxBuffer[RxCounter-1] == '5'){
			Usart_SendString(USART1, "ok\n");
			printf("%d", RxCounter);
			FLASH_WriteByte(ADDR, aRxBuffer, RxCounter);
		}
		RxCounter = 0;
	}					
} 
		
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	{
			
	}
   
    return ch;
}


int fgetc(FILE *f)
{
	while( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
	{
		
	}
	
		return (int)USART_ReceiveData(USART1);
}










