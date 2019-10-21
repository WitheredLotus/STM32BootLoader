#include "flash.h"


//在指定地址写入数组
void FLASH_WriteByte(u32 addr , u8 *p , u16 Byte_Num)
{
	
	      u16 HalfWord;						//待写入的半字
        Byte_Num = Byte_Num/2;	//半字个数
        FLASH_Unlock();					//解锁
        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	//清除标志
        FLASH_ErasePage(addr);	//擦除一页 默认是1K
        while(Byte_Num --)
        {
                HalfWord=*(p++);
                HalfWord|=*(p++)<<8;
                FLASH_ProgramHalfWord(addr, HalfWord);	//写入半字
                addr += 2;
        }
        FLASH_Lock();		//上锁
}

//在指定地址读出数组
void FLASH_ReadByte(u32 addr , u8 *p , u16 Byte_Num)
{
			while(Byte_Num--)
		 {
				*(p++)=*((uint8_t*)addr++);
		 }
		
}
