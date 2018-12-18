#include "stmflash.h"
#include "MENU.H"
extern ShowStr showNature;
//读取指定地址的字(32位数据) 
//faddr:读地址 
//返回值:对应数据.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *( __IO u32*)faddr; 
}

//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为4的倍数!!)
//pBuffer:数据指针
//NumToWrite:字(32位)数(就是要写入的32位数据的个数.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
	
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError = 0;
	EraseInitStruct.NbPages = 1;//要擦除的页数,1页有2KB
	EraseInitStruct.PageAddress = WriteAddr;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	
	HAL_FLASH_Unlock();             //解锁	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	FLASH_WaitForLastOperation(1000);            //等待上次操作完成
	 while(NumToWrite)//写数据
	 {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,WriteAddr,*pBuffer);//写入数据
		WriteAddr+=4;
		pBuffer++;
		NumToWrite -- ;
	}  

	HAL_FLASH_Lock();           //上锁
} 

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(32位)数
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{	
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.

	}
}

//初始化表头的数据
void FlashData_Init(ShowStr* showStr)
{
	u32 dat = FLASH_INIT_DATA;

	if(dat != STMFLASH_ReadWord(FLASH_INIT_SECTOR))	//如果没有被初始化就初始化FLASH
	{
			STMFLASH_Write(FLASH_INIT_SECTOR,&dat,1);	//保存初始化数值
			showStr->baud = Baud_19200;
			showStr->MailAddr = 1;
			showStr->Language = CHINESE;	
			showStr->Resolution_AddUpTJLL = 0;
			showStr->Resolution_AddUpZLLL = 0;
			showStr->Resolution_InstantTJLL = 0;
			showStr->Resolution_InstantZLLL = 0;
			showStr->Resolution_MediumDensity = 0;
			showStr->FreUper = 10000;
			showStr->PulesWith = 50;
			showStr->Interface = 0;
			showStr->signalSelect1 = 0;
			showStr->signalSelect2 = 0;
			showStr->SelectControlPar = 0;
			showStr->ValidControlForm = HIGH;
			showStr->quDongFudu = 0;
			showStr->PassWord = 1234;
			STMFLASH_Write(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);	//保存数值
	}
		STMFLASH_Read(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);		//读数据

	
}



