/******************************************************************************
*
* (c) Copyright 2012 Peleng, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Peleng, Inc.
* and is protected under BY Reports and international copyright and other
* intellectual property laws.
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/*****************************************************************************/
/**
* @file eeprommajor.c
*
* Put short file description here  !
*
* 	Created on: 28.04.2013
*   	Author: mollex
*
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a    			  First release
*
******************************************************************************/

/****************************** Include Files *******************************/
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <avr/eeprom.h>
/************************** Constant Definitions ****************************/
/* defines for future compatibility */
#ifndef cbi
	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


#define EEPROM_MAJOR1		0
#define EEPROM_MAJOR2		128
#define EEPROM_MAJOR3		256
/**************************** Type Definitions ******************************/
/***************** Macros (Inline Functions) Definitions ********************/
/************************** Variable Definitions ****************************/
/************************** Function Prototypes *****************************/
/**<
 * **************************************************************************
 * @brief	Function save eeprom major 1 byte
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void eprom_majorsave(unsigned short addr, unsigned char val)
{
	eeprom_write_byte ((uint8_t *)(addr + EEPROM_MAJOR1), val);
	if(val & 0x80) {val <<=1; val |= 1;} else val<<=1;
	eeprom_write_byte ((uint8_t *)(addr + EEPROM_MAJOR2), val);
	if(val & 0x80) {val <<=1; val |= 1;} else val<<=1;
	eeprom_write_byte ((uint8_t *)(addr + EEPROM_MAJOR3), val);
}
/**<
 * **************************************************************************
 * @brief	Function load eeprom major 1 byte
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
char eprom_majorload(unsigned short addr)
{
	char v1, v2, v3;
	v1 = eeprom_read_byte ((uint8_t *)(addr + EEPROM_MAJOR1));
	v2 = eeprom_read_byte ((uint8_t *)(addr + EEPROM_MAJOR2));
	v3 = eeprom_read_byte ((uint8_t *)(addr + EEPROM_MAJOR3));

	if(v2 & 0x01) {v2 >>=1; v2 |= 0x80;} else v2>>=1;
	if(v3 & 0x01) {v3 >>=1; v3 |= 0x80;} else v3>>=1;
	if(v3 & 0x01) {v3 >>=1; v3 |= 0x80;} else v3>>=1;

	return ((v1 & v2) | (v1 & v3) | (v2 & v3));
}
/**<
 * **************************************************************************
 * @brief	Function save eeprom
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
/*void Eprom_SaveVal(char *b, unsigned char size)
{
	unsigned short addr = 0x40;
	while(size--)
	{
		eprom_majorsave(addr++, *b++);
	}
	eeprom_read_byte(0);
	tx_print("\n\rSave Eeprom Ok\n\r");
}*/
/**<
 * **************************************************************************
 * @brief	Function load eeprom
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
/*void Eprom_LoadVal(char *b, unsigned char size)
{
	unsigned short addr = 0x40;
	while(size--)
	{
		*b++ = eprom_majorload(addr++);
	}
	eeprom_read_byte(0);
	tx_print("\n\rLoad Eeprom Ok\n\r");
}*/
/**<
 * **************************************************************************
 * @brief	Function save eeprom
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void Eprom_MjrSave(unsigned char addr, char val)
{
	eprom_majorsave(addr, val);
	eeprom_read_byte(0);
}
/**<
 * **************************************************************************
 * @brief	Function load eeprom
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
char Eprom_MjrLoad(unsigned char addr)
{
	char val = eprom_majorload(addr);
	eeprom_read_byte(0);
	return val;
}
