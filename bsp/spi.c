/*
 * spi.c
 *
 *  Created on: 25.11.2012
 *      Author: Admin
 */
/*****************************************************************************/
/**
* spi.c
*
*  Created on: 25.11.2012
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

#include "gl.h"
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
volatile char spi_dmdchannel;
volatile char spi_dmdrow;
volatile char spi_dmdi;
volatile char spi_dmdj;
/************************** Function Prototypes ******************************/
/**<
 * **************************************************************************
 * @brief	Function interrupt UART recv
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
ISR(SPI_STC_vect)
 {
	//tx_print_usart("I  ");
	//spi_buff[0] = SPDR;
/*	if(spi_count <= 2)
	{
		SPDR = spi_count++;
	}*/

	if(spi_dmdj != 0x10)
	{
		spi_dmdrow -=4;
		SPDR = ~_VideoBuf.vbuff[spi_dmdj][spi_dmdi][spi_dmdrow + spi_dmdchannel];

		if(spi_dmdrow == 0)
		{
			spi_dmdrow = 12+4;

			if(++spi_dmdi > 7)
			{
				spi_dmdi = 0;
				if(spi_dmdj == 0) spi_dmdj = 0x11;
				spi_dmdj--;
			}
		}
	}
 }
/**<
 * **************************************************************************
 * @brief	Function send char by different interface
 *
 * @param 	b. 	char send value
 * @return  None.
 ***************************************************************************/
void spi_send(char b)
{
	//SPDR = b;
	spi_dmdchannel = b;
	spi_dmdrow = 12;
	spi_dmdi= 0;
	spi_dmdj = 1;
	SPDR = ~_VideoBuf.vbuff[spi_dmdj][spi_dmdi][spi_dmdrow + spi_dmdchannel];
}
/**<
 * **************************************************************************
 * @brief	Function send then get char by different interface
 *
 * @param 	b. 	char send value
 * @return  Char.	Receive value
 ***************************************************************************/
char spi_transfer(char b)
{
	  SPDR = b;
	  while (!(SPSR & _BV(SPIF)))
	    ;
	  return SPDR;
}
/**<
 * **************************************************************************
 * @brief	Function initializing peripherals
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void spi_init()
{
	DDRB |= (_BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5));
	  // SPI prescaler:
	  // SPI2X SPR1 SPR0
	  //   0     0     0    fosc/4
	  //   0     0     1    fosc/16
	  //   0     1     0    fosc/64
	  //   0     1     1    fosc/128
	  //   1     0     0    fosc/2                    << Set in this instance
	  //   1     0     1    fosc/8
	  //   1     1     0    fosc/32
	  //   1     1     1    fosc/64

	SPCR |= ( (1<<SPE) | (1<<MSTR) | (1<<DORD) | (1<<SPIE) ); // enable SPI as master
	//SPCR |= ( (1<<SPE) | (1<<MSTR) | (1<<DORD)  ); // enable SPI as master
	SPCR &= ~( (1<<SPR1) | (1<<SPR0) );           // clear prescaler bits
	//SPCR |= ( (1<<SPR1) | (1<<SPR0)  | (1<<CPOL));  // clear prescaler bits
	SPSR |= (1<<SPI2X);
}
