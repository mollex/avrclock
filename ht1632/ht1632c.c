/******************************************************************************
*
* (c) Copyright 2011 Peleng, Inc. All rights reserved.
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
* @file ht1632c.c
*
* Put short file description here  !
*
* 	Created on:  Feb 27, 2012
*   	Author: mollex
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
/************************** Constant Definitions ****************************/
#define HT_WR		2
#define HT_DATA		1
#define HT_CS		5
#define HT_CLK		4
#define HT_PORT		PORTC
#define HT_DDR		DDRC

#define HT1632C_CHIP_MAX		4

/*
	All the various commands
*/
#define HT1632_ID_CMD 4		/* ID = 100 - Commands */
#define HT1632_ID_RD  6		/* ID = 110 - Read RAM */
#define HT1632_ID_WR  5		/* ID = 101 - Write RAM */

#define HT1632_CMD_SYSDIS 0x00	/* CMD= 0000-0000-x Turn off oscil */
#define HT1632_CMD_SYSON  0x01	/* CMD= 0000-0001-x Enable system oscil */
#define HT1632_CMD_LEDOFF 0x02	/* CMD= 0000-0010-x LED duty cycle gen off */
#define HT1632_CMD_LEDON  0x03	/* CMD= 0000-0011-x LEDs ON */
#define HT1632_CMD_BLOFF  0x08	/* CMD= 0000-1000-x Blink OFF */
#define HT1632_CMD_BLON   0x09	/* CMD= 0000-1001-x Blink On */
#define HT1632_CMD_SLVMD  0x10	/* CMD= 0001-00xx-x Slave Mode */
#define HT1632_CMD_MSTMD  0x14	/* CMD= 0001-01xx-x Master Mode */
#define HT1632_CMD_RCCLK  0x18	/* CMD= 0001-10xx-x Use on-chip clock */
#define HT1632_CMD_EXTCLK 0x1C	/* CMD= 0001-11xx-x Use external clock */
#define HT1632_CMD_COMS00 0x20	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS01 0x24	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS10 0x28	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS11 0x2C	//P-MOS OUTPUT AND 16COMMON OPTION
 /* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_PWM    0xA0	/* CMD= 101x-PPPP-x PWM duty cycle */

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/
/* defines for future compatibility */
#ifndef cbi
	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/************************** Variable Definitions ****************************/

/************************** Function Prototypes ******************************/
extern void ht1632c_Init();
extern void chipselect74164(int8_t chipNo);
extern void  ht1632c_test(int8_t chipNo, uint8_t adress, uint8_t value);

/*
static void  drw_printVideoBuffOnConsole(uint8_t *bptr, size_t len){

	printf("\f");
	uint16_t i,j;
	for(i=0; i < 8; i++){
		for(j=0; j < len; j++){
			if(bptr[j] & (1<<i)) printf("#");
			else printf(".");
		}
		printf("\r\n");
	}
}
*/
void chipselect74164(int8_t chipNo)
{
	if(chipNo < 0)
	{
		cbi(HT_PORT, HT_CS);
		for(uint8_t tmp=0; tmp<HT1632C_CHIP_MAX; tmp++) {
			sbi(HT_PORT, HT_CLK);
			cbi(HT_PORT, HT_CLK);
		}
	}
	else
	{
		sbi(HT_PORT, HT_CS);
	    for(uint8_t tmp=0; tmp<HT1632C_CHIP_MAX; tmp++) {
	    	sbi(HT_PORT, HT_CLK);
	    	cbi(HT_PORT, HT_CLK);
	    }
	    if(chipNo > 0)
	    {
			cbi(HT_PORT, HT_CS);
			sbi(HT_PORT, HT_CLK);
			cbi(HT_PORT, HT_CLK);
			sbi(HT_PORT, HT_CS);
			for(uint8_t tmp=1 ; tmp<chipNo; tmp++) {
				sbi(HT_PORT, HT_CLK);
				cbi(HT_PORT, HT_CLK);
			}
	    }
	}
}

 void writebitsMSB(uint8_t value, uint8_t len)
{
	  for (int i=len-1; i>=0; i--) {
		 cbi(HT_PORT, HT_WR);
		if (value & 1<<i) {
		 sbi(HT_PORT, HT_DATA);
		}
		else {
		 cbi(HT_PORT, HT_DATA);
		}
		 sbi(HT_PORT, HT_WR);
	  }
}

 void writebitsLSB(uint8_t value, uint8_t len)
{
	  for (int i=0; i<len; i++) {
		 cbi(HT_PORT, HT_WR);
		if (value & 1<<i) {
		 sbi(HT_PORT, HT_DATA);
		}
		else {
		 cbi(HT_PORT, HT_DATA);
		}
		 sbi(HT_PORT, HT_WR);
	  }
}

void sendcmd (int8_t chipNo, uint8_t command)
{
  chipselect74164(chipNo);
  writebitsMSB(HT1632_ID_CMD, 3);  // send 3 bits of id: COMMMAND
  writebitsMSB(command, 8);        // send the actual command
  writebitsMSB(0, 1); 	        	/* one extra dont-care bit in commands. */
  chipselect74164(0);
}

void sendByte(int8_t chipNo, uint8_t adress, uint8_t value)
{

	chipselect74164(chipNo);
	writebitsMSB(HT1632_ID_WR, 3);  // send 3 bits of id: COMMMAND
	writebitsMSB(adress, 7);  		// send 7 bits of id: Address
	writebitsLSB(value, 8);        // send the actual data
}

void ht1632c_memset(uint8_t colour, uint8_t adress, uint8_t value, size_t size)
{
	adress <<= 1;
	size = adress + (size<<1);

	for(uint16_t i=adress; i< size; i+=2)
	{
		if(colour & 0x01)
		{
			sendByte((i >> 5)+1, (i & 0x1F), value);
		}
		if(colour & 0x02)
		{
			sendByte((i >> 5)+1, (i & 0x1F) | 0x20, value);
		}
	}
}

void ht1632c_sendBuffer8(uint8_t colour, uint8_t adress, uint8_t* src, size_t size)
{
	int inx = 0;
	adress <<= 1;
	size = adress + (size<<1);

		for(uint16_t i=adress; i< size; i+=2)
		{
			//printf("src 0x%x \n\r",*src);

			if(colour & 0x01)
			{
				sendByte((i >> 5)+1, (i & 0x1F), src[inx]);
			}
			if(colour & 0x02)
			{
				sendByte((i >> 5)+1, (i & 0x1F) | 0x20, src[inx]);
			}
			inx++;
		}
}




void ht1632c_Init()
{
	HT_DDR  = 0xff;//(_BV(HT_WR) | _BV(HT_DATA) | _BV(HT_CS) | _BV(HT_CLK));
	HT_PORT = 0x00;//~(_BV(HT_WR) | _BV(HT_DATA) | _BV(HT_CS) | _BV(HT_CLK));


	for(uint8_t i=1; i<=HT1632C_CHIP_MAX; i++) {
		sendcmd(i, HT1632_CMD_SYSDIS); // Disable system
		sendcmd(i, HT1632_CMD_COMS00); // 16*32, PMOS drivers
		sendcmd(i, HT1632_CMD_RCCLK);  // MASTER MODE - Use on-chip clock
		sendcmd(i, HT1632_CMD_SYSON);  // System on - Enable system oscil
		sendcmd(i, HT1632_CMD_LEDON);  // LEDs on
		sendcmd(i, HT1632_CMD_PWM+15);
	}


}
