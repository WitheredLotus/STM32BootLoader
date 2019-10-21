#include "ustart.h"


uint8_t aRxBuffer[200]={0x00};
volatile uint8_t RxCounter=0;
volatile uint8_t ReceiveState=0;

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//嵌套中断控制器组选择
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//配置USART 为中断源
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
	
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
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	//打开串口外设时钟
	DEBUG_USART_APBxClkCmd( DEBUG_USART_CLK, ENABLE);
	
	//将USART Tx的GPIO配置为推婉复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	
	//将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	//配置串口的工作模式
	//配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	
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
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	//串口中断优先级配置
	NVIC_Configuration();
	
	//使能串口接收中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
	
	//使能IDLE空闲中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_IDLE, ENABLE);
	

	USART_ClearFlag(USART1,USART_FLAG_TC);
	
	//使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	
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


void DEBUG_USART_IRQHandler(void)
{	
	uint8_t Clear=Clear;//这种定义方法，用来消除编译器的"没有用到"提醒
	
	if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET) // 如果接收到1个字节
	{ 	
		aRxBuffer[RxCounter++] = DEBUG_USARTx->DR;// 把接收到的字节保存，数组地址加1
	} 
	else if(USART_GetITStatus(DEBUG_USARTx, USART_IT_IDLE) != RESET)// 如果接收到1帧数据
	{
		Clear=DEBUG_USARTx->SR;// 读SR寄存器
		Clear=DEBUG_USARTx->DR;// 读DR寄存器(先读SR再读DR，就是为了清除IDLE中断)
		ReceiveState=1;// 标记接收到了1帧数据
	}
						
} 
		
int fputc(int ch, FILE *f)
{
	USART_SendData(DEBUG_USARTx, (uint8_t) ch);

	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET)
	{
			
	}
   
    return ch;
}


int fgetc(FILE *f)
{
	while( USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET)
	{
		
	}
	
		return (int)USART_ReceiveData(DEBUG_USARTx);
}










