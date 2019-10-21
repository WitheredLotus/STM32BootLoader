#include "ustart.h"


uint8_t aRxBuffer[200]={0x00};
volatile uint8_t RxCounter=0;
volatile uint8_t ReceiveState=0;

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Ƕ���жϿ�������ѡ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//����USART Ϊ�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
	
	//��ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	
	//�����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	//ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	//��ʼ������NVIC
	NVIC_Init(&NVIC_InitStructure);
	
	
}


void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//�򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	//�򿪴�������ʱ��
	DEBUG_USART_APBxClkCmd( DEBUG_USART_CLK, ENABLE);
	
	//��USART Tx��GPIO����Ϊ������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	
	//��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	//���ô��ڵĹ���ģʽ
	//���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	
	//����֡�����ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	//����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	
	//����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	
	//����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	//���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	//��ɴ��ڳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	//�����ж����ȼ�����
	NVIC_Configuration();
	
	//ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
	
	//ʹ��IDLE�����ж�
	USART_ITConfig(DEBUG_USARTx, USART_IT_IDLE, ENABLE);
	

	USART_ClearFlag(USART1,USART_FLAG_TC);
	
	//ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);	
}

void Usart_SendByte( USART_TypeDef *pUSARTx, uint8_t ch)
{
	//����һ���ֽ����ݵ�USART
	USART_SendData(pUSARTx,ch);
	
	//�ȴ��������ݼĴ���Ϊ��
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
	uint8_t Clear=Clear;//���ֶ��巽��������������������"û���õ�"����
	
	if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET) // ������յ�1���ֽ�
	{ 	
		aRxBuffer[RxCounter++] = DEBUG_USARTx->DR;// �ѽ��յ����ֽڱ��棬�����ַ��1
	} 
	else if(USART_GetITStatus(DEBUG_USARTx, USART_IT_IDLE) != RESET)// ������յ�1֡����
	{
		Clear=DEBUG_USARTx->SR;// ��SR�Ĵ���
		Clear=DEBUG_USARTx->DR;// ��DR�Ĵ���(�ȶ�SR�ٶ�DR������Ϊ�����IDLE�ж�)
		ReceiveState=1;// ��ǽ��յ���1֡����
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










