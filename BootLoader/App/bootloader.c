#include "bootloader.h"
#include "sys.h"


iapfun jump2app;

//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void fun_jump(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ 
		jump2app=(void(*)())*(vu32*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(vu32*)appxaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		for(int i = 0; i < 8; i++)
		{			
			NVIC->ICER[i] = 0xFFFFFFFF;	/* �ر��ж�*/
			NVIC->ICPR[i] = 0xFFFFFFFF;	/* ����жϱ�־λ */
		}
		jump2app();									//��ת��APP.
	}
}
