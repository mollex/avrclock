/*****************************************************************************/
/**
* ds18x20.c
*
*  Created on: 30.07.2013
*      Author: Admin
*
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a    			  First release
*
******************************************************************************/

/***************************** Include Files *********************************/
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "owi.h"
/************************** Constant Definitions ****************************/

/* DS18X20 specific values (see datasheet) */
#define DS18S20_FAMILY_CODE       0x10
#define DS18B20_FAMILY_CODE       0x28
#define DS1822_FAMILY_CODE        0x22

/**************************** Type Definitions ******************************/
	// typedef for the rom IDs
	// done so we can access the entire id or each individual byte
	typedef struct
	{
		unsigned char find;
		unsigned char type;
		unsigned char tempH;
		unsigned char tempL;
		unsigned char tempP;
		unsigned char byte[8];
	} Dallas_rom_id_t;

	Dallas_rom_id_t     Dallas_rom_id;
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
extern unsigned char dallas_crc;				// current crc global variable
/************************** Function Prototypes ******************************/

extern void tx_print(char *s);
extern void tx_hexprint(char *s, char len);
/**<
 * **************************************************************************
 * @brief	Function initializing peripherals
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
unsigned char ds18x20Init(unsigned char pins)
{
	OWI_Init(pins);
	return (OWI_DetectPresence(pins));
}
/**<
 * **************************************************************************
 * @brief	Function
 *
 * @param 	b. 	char send value
 * @return  None.
 ***************************************************************************/
void ds18x20_SelfTest()
{
	int j;
	Dallas_rom_id.find = 0;

	if(ds18x20Init(DS18B20_PIN))
	{
		OWI_ReadRom(&Dallas_rom_id.byte[0], DS18B20_PIN);  //Читаем РОМ Индификатор
		dallas_crc = 0;
		for(j=0; j<8; j++){	OWI_dallasCRC(Dallas_rom_id.byte[j]);}//Высчитываем CRC
		if(dallas_crc)								//Если 0 то сумма корректна
		{
			printf("Crc Err \n\r");
		}else
		{
			Dallas_rom_id.find = 1;
			Dallas_rom_id.type = Dallas_rom_id.byte[0];
			printf("\n\r Id Rom: ");
			for(j=0; j<8; j++){	printf(" 0x%x", Dallas_rom_id.byte[j]);}
		}
	}else
	{
		printf("Not found \n\r");
	}
}
/**<
 * **************************************************************************
 * @brief	Function
 *
 * @param 	b. 	char send value
 * @return  None.
 ***************************************************************************/
void ds18x20_ReadTemp()
{
	char	 tempBuff[2];

	if(Dallas_rom_id.find == 1)
	{
		OWI_DetectPresence(DS18B20_PIN);
		OWI_SendByte(OWI_ROM_SKIP, DS18B20_PIN);
		OWI_SendByte(DS18B20_CONVERT_TEMP, DS18B20_PIN);
		_delay_ms(1000);

		OWI_DetectPresence(DS18B20_PIN);
		OWI_SendByte(OWI_ROM_SKIP, DS18B20_PIN);
		OWI_SendByte(DS18B20_READ_SCRATCHPAD, DS18B20_PIN);
		tempBuff[1] = OWI_ReceiveByte(DS18B20_PIN);
		tempBuff[0] = OWI_ReceiveByte(DS18B20_PIN);

		if(Dallas_rom_id.type == DS18S20_FAMILY_CODE)
		{


		}else if(Dallas_rom_id.type == DS18B20_FAMILY_CODE)
		{
			Dallas_rom_id.tempH = (tempBuff[1]>>1);

			printf("\n\r 18b20: %d", Dallas_rom_id.tempH);

		}else if(Dallas_rom_id.type == DS1822_FAMILY_CODE)
		{


		}else
		{
			ds18x20_SelfTest();
		}

	}else
	{
		ds18x20_SelfTest();
	}
}
