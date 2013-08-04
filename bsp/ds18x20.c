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

#include "debug.h"
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
		unsigned char tempS;
		unsigned char byte[9];
	} Dallas_rom_id_t;

	Dallas_rom_id_t     Dallas_rom_id;
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
/************************** Function Prototypes ******************************/

extern void tx_print(char *s);
extern void tx_hexprint(char *s, char len);
/**<
 * **************************************************************************
 * @brief	Function
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
unsigned char ds18x20_GetHight()
{
	return (Dallas_rom_id.tempH);
}
unsigned char ds18x20_GetLow()
{
	return (Dallas_rom_id.tempL);
}
unsigned char ds18x20_Sign()
{
	return (Dallas_rom_id.tempS);
}
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

		if(OWI_dallasCRCBuff(Dallas_rom_id.byte, 8))								//Если 0 то сумма корректна
		{
			DEBUG_PRINTF("Crc Err \n\r");
		}else
		{
			Dallas_rom_id.find = 1;
			Dallas_rom_id.type = Dallas_rom_id.byte[0];

			DEBUG_PRINTF("\n\r Id Rom: ");
			for(j=0; j<8; j++){	DEBUG_PRINTF(" 0x%x", Dallas_rom_id.byte[j]);}
		}
	}else
	{
		DEBUG_PRINTF("Not found \n\r");
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
	int i;
	if(Dallas_rom_id.find == 1)
	{
		OWI_DetectPresence(DS18B20_PIN);
		OWI_SendByte(OWI_ROM_SKIP, DS18B20_PIN);
		OWI_SendByte(DS18B20_CONVERT_TEMP, DS18B20_PIN);
		_delay_ms(1000);

		OWI_DetectPresence(DS18B20_PIN);
		OWI_SendByte(OWI_ROM_SKIP, DS18B20_PIN);
		OWI_SendByte(DS18B20_READ_SCRATCHPAD, DS18B20_PIN);

		for ( i = 0; i < 9; i++) {           // we need to read 9 bytes
			 Dallas_rom_id.byte[i] = OWI_ReceiveByte(DS18B20_PIN);
		    }

		if(OWI_dallasCRCBuff(Dallas_rom_id.byte, 9))
		{
			DEBUG_PRINTF("Crc Err \n\r");

		}else
		{
			DEBUG_PRINTF("\n\r Temp: ");
			for(i=0; i<9; i++){	DEBUG_PRINTF(" 0x%x", Dallas_rom_id.byte[i]);}

			// minus sign
			Dallas_rom_id.tempS = Dallas_rom_id.byte[1] & 0x80;
			if(Dallas_rom_id.tempS)
			{
				Dallas_rom_id.byte[0] = ~Dallas_rom_id.byte[0];
				Dallas_rom_id.byte[1] = ~Dallas_rom_id.byte[1];
			}

			if(Dallas_rom_id.type == DS18S20_FAMILY_CODE)
			{
				Dallas_rom_id.tempH = (Dallas_rom_id.byte[0]>>1);
				Dallas_rom_id.tempL = (Dallas_rom_id.byte[0] & 0x01) ? 5 : 0;

			}else if(Dallas_rom_id.type == DS18B20_FAMILY_CODE || Dallas_rom_id.type == DS1822_FAMILY_CODE)
			{
				Dallas_rom_id.tempH = Dallas_rom_id.byte[0]>>4 | Dallas_rom_id.byte[1]<<4;
				Dallas_rom_id.tempL = ((Dallas_rom_id.byte[0] + 1) & 0x08) ? 5 : 0;

			}else
			{
				ds18x20_SelfTest();
			}
		}

	}else
	{
		ds18x20_SelfTest();
	}
}
