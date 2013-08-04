/*--------------------------------------------------------------------------------------

dmdp10.c  - Function and support library for the Freetronics DMD, a 512 LED matrix display
           panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 Note that the DMD library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the DMD is being written to.


LED Panel Layout in RAM
                            32 pixels (4 bytes)
        top left  ----------------------------------------
                  |                                      |
         Screen 1 |        512 pixels (64 bytes)         | 16 pixels
                  |                                      |
                  ---------------------------------------- bottom right

 ---

 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
/*****************************************************************************/
/**
* @file dmdp10.c
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

#include "gl.h"
/************************** Constant Definitions ****************************/

// ######################################################################################################################
// ######################################################################################################################
//#warning CHANGE THESE TO SEMI-ADJUSTABLE PIN DEFS!
//Arduino pins used for the display connection
#define PIN_DMD_nOE       6    // D9 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A         0    // D0
#define PIN_DMD_B         7    // D7
#define PIN_DMD_CLK       5   // D13_SCK  is SPI Clock if SPI is used
#define PIN_DMD_SCLK      1    // D8
#define PIN_DMD_R_DATA    3   // D11_MOSI is SPI Master Out if SPI is used
//Define this chip select pin that the Ethernet W5100 IC or other SPI device uses
//if it is in use during a DMD scan request then scanDisplayBySPI() will exit without conflict! (and skip that scan)

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/
/* defines for future compatibility */
#ifndef cbi
	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//DMD I/O pin macros
#define LIGHT_DMD_ROW_01_05_09_13()       { cbi( PORTD, PIN_DMD_B ); cbi( PORTB, PIN_DMD_A ); }
#define LIGHT_DMD_ROW_02_06_10_14()       { cbi( PORTD, PIN_DMD_B ); sbi( PORTB, PIN_DMD_A ); }
#define LIGHT_DMD_ROW_03_07_11_15()       { sbi( PORTD, PIN_DMD_B ); cbi( PORTB, PIN_DMD_A ); }
#define LIGHT_DMD_ROW_04_08_12_16()       { sbi( PORTD, PIN_DMD_B ); sbi( PORTB, PIN_DMD_A ); }

#define LATCH_DMD_SHIFT_REG_TO_OUTPUT()   { sbi( PORTB, PIN_DMD_SCLK ); cbi( PORTB,  PIN_DMD_SCLK ); }
#define OE_DMD_ROWS_OFF()                 { cbi( PORTD, PIN_DMD_nOE ); }
#define OE_DMD_ROWS_ON()                  { sbi( PORTD, PIN_DMD_nOE ); }

/************************** Variable Definitions ****************************/

/************************** Function Prototypes ******************************/
extern void spi_init();
extern char spi_transfer(char b);
void dmdp10_Scan();

/**<
 * **************************************************************************
 * @brief	Timer Intr for scan every 4.096 ms
 *					scan time 50 us - cpu 16Mhz  spi 8Mhz  32x16 pixels
 *					scan time 80 us - cpu 16Mhz  spi 8Mhz  64x16 pixels
 *					scan time 160 us -cpu 16Mhz  spi 8Mhz  64x32 pixels
 * @param 	None.
 * @return  None.
 ***************************************************************************/
ISR (TIMER2_OVF_vect)
{
	 dmdp10_Scan();
}
/**<
 * **************************************************************************
 * @brief	Scan for 1 module
 *
 *		_____________
 *		|			|
 *	   -|	 M1		|-
 *		|___________|
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
/*inline void dmdp10_scanSingleModule(char chnl)
{
	for (int i=0;i<4;i++) {

		spi_transfer(~VideoBuf.vbuff[0][i][12 + chnl]);
		spi_transfer(~VideoBuf.vbuff[0][i][8 + chnl]);
		spi_transfer(~VideoBuf.vbuff[0][i][4 + chnl]);
		spi_transfer(~VideoBuf.vbuff[0][i][0 + chnl]);
    }
}*/
/**<
 * **************************************************************************
 * @brief	Scan for 1 module
 *
 *		_____________			_____________
 *		|			|			|			|
 *	   -|	 M1		|-----------|	 M2		|-
 *		|___________|			|___________|
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
/*inline void dmdp10_scanDoubleModule(char chnl)
{
	for (int i=0;i<8;i++) {

		spi_transfer(~VideoBuf.vbuff[0][i][12 + chnl]);
		spi_transfer(~VideoBuf.vbuff[0][i][8 + chnl]);
		spi_transfer(~VideoBuf.vbuff[0][i][4 + chnl]);
		spi_transfer(~VideoBuf.vbuff[0][i][0 + chnl]);

    }
}*/
/**<
 * **************************************************************************
 * @brief	Scan for 1 module
 *
 *		_____________			_____________
 *		|			|			|			|
 *	   -|	 M1		|-----------|	 M2		|----
 *		|___________|			|___________|	|
 *												|
 *	  ------------------------------------------
 * 	 |	_____________			_____________
 *	 |	|			|			|			|
 *	 | -|	 M3		|-----------|	 M4		|-
 *		|___________|			|___________|
 * @param 	None.
 * @return  None.
 ***************************************************************************/
inline void dmdp10_scanQadroModule(char chnl)
{
	int j = 1;
	do
	{
		for (int i=0;i<8;i++) {

			spi_transfer(~_VideoBuf.vbuff[j][i][12 + chnl]);
			spi_transfer(~_VideoBuf.vbuff[j][i][8 + chnl]);
			spi_transfer(~_VideoBuf.vbuff[j][i][4 + chnl]);
			spi_transfer(~_VideoBuf.vbuff[j][i][0 + chnl]);
		}
	}while(j--);
}
/**<
 * **************************************************************************
 * @brief	Function scan led module
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void dmdp10_Scan()
{
	static uint8_t chnl = 0;

	if(chnl>3) chnl = 0;

	dmdp10_scanQadroModule(chnl);

	OE_DMD_ROWS_OFF();
	LATCH_DMD_SHIFT_REG_TO_OUTPUT();

    switch (chnl) {
       case 0:			// row 1, 5, 9, 13 were clocked out
           LIGHT_DMD_ROW_01_05_09_13();
           break;
       case 1:			// row 2, 6, 10, 14 were clocked out
           LIGHT_DMD_ROW_02_06_10_14();
           break;
       case 2:			// row 3, 7, 11, 15 were clocked out
           LIGHT_DMD_ROW_03_07_11_15();
           break;
       case 3:			// row 4, 8, 12, 16 were clocked out
           LIGHT_DMD_ROW_04_08_12_16();
           break;
       }

	OE_DMD_ROWS_ON();

	chnl++;
}
/**<
 * **************************************************************************
 * @brief	Function initializing peripherals
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void dmdp10_Init()
{
	DDRB  = (1<<PIN_DMD_A) | (1<<PIN_DMD_SCLK);
	PORTB = 0x00;

	DDRD  = (1<<PIN_DMD_B) | (1<<PIN_DMD_nOE);
	PORTD= 0x00;

	spi_init();

#if defined (__AVR_ATmega8__)

		TCCR2 = 1<<CS22 | 1<<CS20;			//divide by 128
		TIMSK = 1<<TOIE2;			//enable timer interrupt

#else
		TCCR2B = 1<<CS02;			//divide by 256
		TIMSK2 = 1<<TOIE0;			//enable timer interrupt
#endif


}
