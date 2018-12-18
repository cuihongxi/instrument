#include "stmflash.h"
#include "MENU.H"
extern ShowStr showNature;
//��ȡָ����ַ����(32λ����) 
//faddr:����ַ 
//����ֵ:��Ӧ����.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *( __IO u32*)faddr; 
}

//��ָ����ַ��ʼд��ָ�����ȵ�����
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
	
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError = 0;
	EraseInitStruct.NbPages = 1;//Ҫ������ҳ��,1ҳ��2KB
	EraseInitStruct.PageAddress = WriteAddr;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	
	HAL_FLASH_Unlock();             //����	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	FLASH_WaitForLastOperation(1000);            //�ȴ��ϴβ������
	 while(NumToWrite)//д����
	 {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,WriteAddr,*pBuffer);//д������
		WriteAddr+=4;
		pBuffer++;
		NumToWrite -- ;
	}  

	HAL_FLASH_Lock();           //����
} 

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(32λ)��
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{	
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.

	}
}

//��ʼ����ͷ������
void FlashData_Init(ShowStr* showStr)
{
	u32 dat = FLASH_INIT_DATA;

	if(dat != STMFLASH_ReadWord(FLASH_INIT_SECTOR))	//���û�б���ʼ���ͳ�ʼ��FLASH
	{
			STMFLASH_Write(FLASH_INIT_SECTOR,&dat,1);	//�����ʼ����ֵ
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
			STMFLASH_Write(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);	//������ֵ
	}
		STMFLASH_Read(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);		//������

	
}



