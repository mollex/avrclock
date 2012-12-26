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
#define _mDMD_ROW_INIT()    { sbi( DDRD, 2 ); sbi( DDRD, 3 ); sbi( DDRD, 4 ); sbi( DDRD, 5 ); }
#define _mDMD_ROW(a) 		{ PORTD = (PORTD & (~((1<<2) | (1<<3) | (1<<4) | (1<<5))) ) | (a<<2);}
#define _mDMD_ROW_01()      { cbi( PORTD, 2 ); cbi( PORTD, 3 ); cbi( PORTD, 4 ); cbi( PORTD, 5 ); }
#define _mDMD_ROW_02()      { sbi( PORTD, 2 ); cbi( PORTD, 3 ); cbi( PORTD, 4 ); cbi( PORTD, 5 ); }
#define _mDMD_ROW_03()      { cbi( PORTD, 2 ); sbi( PORTD, 3 ); cbi( PORTD, 4 ); cbi( PORTD, 5 ); }
#define _mDMD_ROW_04()      { sbi( PORTD, 2 ); sbi( PORTD, 3 ); sbi( PORTD, 4 ); sbi( PORTD, 5 ); }

#define _mDMD_LATCH_INIT()   		{ sbi( DDRB, 0 ); }
#define _mDMD_LATCH()   	{ sbi( PORTB, 0 ); cbi( PORTB,  0 ); }

#define _mDMD_OE_INIT()     { sbi( DDRB, 1 ); }
#define _mDMD_OE_OFF()      { cbi( PORTB, 1 ); }
#define _mDMD_OE_ON()       { sbi( PORTB, 1 ); }

#define _mDMD_G1_INIT()     { sbi( DDRD, 7 ); }
#define _mDMD_G1_OFF()      { cbi( PORTD, 7 ); }
#define _mDMD_G1_ON()       { sbi( PORTD, 7 ); }

#define _mDMD_G2_INIT()     { sbi( DDRD, 6 ); }
#define _mDMD_G2_OFF()      { cbi( PORTD, 6 ); }
#define _mDMD_G2_ON()       { sbi( PORTD, 6 ); }

/************************** Variable Definitions ****************************/

/************************** Function Prototypes ******************************/
void xinit_spi1(void);		/* Initialize SPI port */
void xlow_spi1(uint16_t d);		/* Send a byte  */
void xhigh_spi1(uint16_t d);	/* Send a byte  */
void xshort_spi1(uint16_t d);

void xinit_spi2(void);		/* Initialize SPI port */

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
	uint8_t val;
	if(chnl>15) chnl = 0;

	for (int i=0;i<4;i++) {

		//val =  (VideoBuf.vbuff[1][i][chnl]<<8)| (VideoBuf.vbuff[0][i][chnl] & 0xFF);
		xshort_spi1(VideoBuf.vbuff[0][i][chnl]);
		//val =  (VideoBuf.vbuff[1][i][chnl] & 0xFF00)| (VideoBuf.vbuff[0][i][chnl] >> 8);
		//xshort_spi1(val);

	}

    //_mDMD_OE_ON();

	_mDMD_LATCH();

	_mDMD_ROW(chnl);

	_mDMD_OE_OFF();

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
	_mDMD_ROW_INIT();
	_mDMD_LATCH_INIT();
	_mDMD_OE_INIT();
	_mDMD_G1_INIT(); _mDMD_G1_OFF();
	_mDMD_G2_INIT(); _mDMD_G2_OFF();

	xinit_spi1();
	xinit_spi2();

	TCCR0B = 1<<CS02;			//divide by 256
	TIMSK0 = 1<<TOIE0;			//enable timer interrupt
}
