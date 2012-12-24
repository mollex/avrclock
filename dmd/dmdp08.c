/*--------------------------------------------------------------------------------------

dmdp10.c  - Function and support library for the Freetronics DMD, a 512 LED matrix display
           panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 Note that the DMD library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the DMD is being written to.


LED Panel Layout in RAM
                            64 pixels (8 bytes)
        top left  ----------------------------------------
                  |                                      |
         Screen 1 |        2048 pixels (256 bytes)       | 32 pixels
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
* @file dmd12.c
*
* Put short file description here  !
*
*  Created on: 22.12.2012
*      Author: mollex
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
#define PIN_DMD_nOE       9    // D9 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A         6    // D6
#define PIN_DMD_B         7    // D7
#define PIN_DMD_CLK       13   // D13_SCK  is SPI Clock if SPI is used
#define PIN_DMD_SCLK      8    // D8
#define PIN_DMD_R_DATA    11   // D11_MOSI is SPI Master Out if SPI is used
//Define this chip select pin that the Ethernet W5100 IC or other SPI device uses
//if it is in use during a DMD scan request then scanDisplayBySPI() will exit without conflict! (and skip that scan)
#define PIN_OTHER_SPI_nCS 10

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
#define LIGHT_DMD_ROW_01_05_09_13()       { cbi( PORTD, 7 ); cbi( PORTD, 6 ); }
#define LIGHT_DMD_ROW_02_06_10_14()       { cbi( PORTD, 7 ); sbi( PORTD, 6 ); }
#define LIGHT_DMD_ROW_03_07_11_15()       { sbi( PORTD, 7 ); cbi( PORTD, 6 ); }
#define LIGHT_DMD_ROW_04_08_12_16()       { sbi( PORTD, 7 ); sbi( PORTD, 6 ); }

#define LATCH_DMD_SHIFT_REG_TO_OUTPUT()   { sbi( PORTB, 0 ); cbi( PORTB,  0 ); }
#define OE_DMD_ROWS_OFF()                 { cbi( PORTB, 1 ); }
#define OE_DMD_ROWS_ON()                  { sbi( PORTB, 1 ); }

/************************** Variable Definitions ****************************/

/************************** Function Prototypes ******************************/
void xinit_spi1 (void);		/* Initialize SPI port */
void xlow_spi1(uint16_t d);		/* Send a byte  */
void xhigh_spi1(uint16_t d);	/* Send a byte  */

void dmdp08_Scan();

extern VideoBuf_t	VideoBuf;

/**<
 * **************************************************************************
 * @brief	Timer Intr for scan every 5 ms
 *					scan time 2.08 ms
 * @param 	None.
 * @return  None.
 ***************************************************************************/
ISR (TIMER0_OVF_vect)
{
	//xlow_spi1(0x81);
	 dmdp08_Scan();
}
/**<
 * **************************************************************************
 * @brief	Function scan led module
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void dmdp08_Scan()
{
	static uint8_t chnl = 0;

	if(chnl>3) chnl = 0;

	for (int i=0;i<2;i++) {

		xlow_spi1(VideoBuf.vbuff[0][i][12 + chnl]);
		xlow_spi1(VideoBuf.vbuff[0][i][8 + chnl]);
		xlow_spi1(VideoBuf.vbuff[0][i][4 + chnl]);
		xlow_spi1(VideoBuf.vbuff[0][i][0 + chnl]);

		xhigh_spi1(VideoBuf.vbuff[0][i][12 + chnl]);
		xhigh_spi1(VideoBuf.vbuff[0][i][8 + chnl]);
		xhigh_spi1(VideoBuf.vbuff[0][i][4 + chnl]);
		xhigh_spi1(VideoBuf.vbuff[0][i][0 + chnl]);

    }

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
void dmdp08_Init()
{
	DDRB  = (1<<0) | (1<<1);
	PORTB = 0x00;

	DDRD  = (1<<7) | (1<<6);
	PORTD= 0x00;

	xinit_spi1();

	TCCR0B = 1<<CS02;			//divide by 256
	TIMSK0 = 1<<TOIE0;			//enable timer interrupt
}
