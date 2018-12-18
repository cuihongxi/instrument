

#include "uhead.h"
#include "spi.h"


#define POWER_UP_INTERRUPT                          0x0003//0xFFF


#define SPICLKPW		1

//---------------------------------
//General definitions
//---------------------------------
#define	BYTE	unsigned char
#define WORD	unsigned int
#define DWORD	unsigned long int

//For the memory map of the ADuC841 registers
#define STAGE_START_ADDRESS		10
#define NB_OF_REGS_PER_STAGE	36
#define NB_OF_CONN_REGS			8
#define REGISTER_LENGTH			16

//---------------------------------
//Global variables
//---------------------------------
extern WORD  AD7147Registers[24];	//[0...23 inc]=1st set of registers [0...23 inc]
								//Element[23] = 0x17 = ID register @ 0x17

#define	AD7147_WrDat(d)	HAL_SPI_Transmit(&hspi3,(uint8_t *)(&(d)),1,2000);	//
#define	AD7147_RdDat(d)	HAL_SPI_Receive(&hspi3,(uint8_t *)(&(d)),1,2000);

#define	AD7147_CS_1		HAL_GPIO_WritePin(AD7147_CS_GPIO_Port,AD7147_CS_Pin,GPIO_PIN_SET);
#define	AD7147_CS_0		HAL_GPIO_WritePin(AD7147_CS_GPIO_Port,AD7147_CS_Pin,GPIO_PIN_RESET);

void WriteToAD7147(const WORD RegisterAddress, const BYTE NumberOfRegisters, WORD *DataBuffer, const BYTE OffsetInBuffer);
void ReadFromAD7147(const WORD RegisterStartAddress, const BYTE NumberOfRegisters, WORD *DataBuffer, const WORD OffsetInBuffer);
void ConfigAD7147(void);
int ServiceAD7147Isr(void);

