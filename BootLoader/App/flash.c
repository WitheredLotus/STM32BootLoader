#include "flash.h"


//��ָ����ַд������
void FLASH_WriteByte(u32 addr , u8 *p , u16 Byte_Num)
{
	
	      u16 HalfWord;						//��д��İ���
        Byte_Num = Byte_Num/2;	//���ָ���
        FLASH_Unlock();					//����
        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	//�����־
        FLASH_ErasePage(addr);	//����һҳ Ĭ����1K
        while(Byte_Num --)
        {
                HalfWord=*(p++);
                HalfWord|=*(p++)<<8;
                FLASH_ProgramHalfWord(addr, HalfWord);	//д�����
                addr += 2;
        }
        FLASH_Lock();		//����
}

//��ָ����ַ��������
void FLASH_ReadByte(u32 addr , u8 *p , u16 Byte_Num)
{
			while(Byte_Num--)
		 {
				*(p++)=*((uint8_t*)addr++);
		 }
		
}
