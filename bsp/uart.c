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
* @file uart.c
*
* Put short file description here  !
*
* 	Created on: Dec 16, 2011
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


/************************** Constant Definitions ****************************/

/* initialize UART(s) depending on CPU defined */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)

#define UCSRXA		UCSR0A
#define UCSRXB		UCSR0B
#define UCSRXC		UCSR0C
#define UBRRXH		UBRR0H
#define UBRRXL		UBRR0L
#define UDRX		UDR0

#elif defined(__AVR_ATmega8__)

#define UCSRXA		UCSRA
#define UCSRXB		UCSRB
#define UCSRXC		UCSRC
#define UBRRXH		UBRRH
#define UBRRXL		UBRRL
#define UDRX		UDR

#define RXEN0		RXEN
#define TXEN0		TXEN
#define RXCIE0		RXCIE
#define TXCIE0		TXCIE
#define UCSZ00		UCSZ0
#define UCSZ01		UCSZ1
#define UDRE0		UDRE
#define RXC0		RXC
#define U2X0		U2X

#endif

/**************************** Type Definitions ******************************/
//#define F_CPU			10000000
#define BAUD_RATE		38400
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
uint8_t uartIsTmout;
/************************** Function Prototypes *****************************/
void uart_putch(char ch);

FILE mystdout = FDEV_SETUP_STREAM(uart_putch, NULL,
                                           _FDEV_SETUP_WRITE);
/**<
 * **************************************************************************
 * @brief	Function interrupt UART recv
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/

ISR(USART_RX_vect)
 {
	
 }

/**<
 * **************************************************************************
 * @brief	Function send char by different interface
 *
 * @param 	ch. 	char send value
 * @return  None.
 ***************************************************************************/
void uart_putch(char ch)
{
	while (!(UCSRXA & (1<<UDRE0)));
	UDRX = ch;
}
/**<
 * **************************************************************************
 * @brief	Function get char by different interface
 *
 * @param 	None.
 * @return  Char.	Receive value
 ***************************************************************************/
char uart_getch()
{
	char ch;
	while(!(UCSRXA & (1<<RXC0))) {}
	ch = UDRX;
	uart_putch(ch);
	return (ch);
}
/**<
 * **************************************************************************
 * @brief	Function disable RX interrupt
 *
 * @param 	char.	Enable/Disable
 * @return  none.
 ***************************************************************************/
void uart_rxIntr(char b)
{
	if(b)	UCSRXB |=  _BV(RXCIE0);
	else UCSRXB &=  ~_BV(RXCIE0);
}

/**<
 * **************************************************************************
 * @brief	Function initializing peripherals
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void uart_init()
{
	DDRD &= ~(0x03);

	UCSRXB = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
	UCSRXC = _BV(UCSZ00) | _BV(UCSZ01);

	uint16_t baud_setting;
	UCSRXA = _BV(U2X0); //Double speed mode USART0
	baud_setting = (F_CPU / 4 / BAUD_RATE - 1) / 2;

	UBRRXH = (baud_setting>>8);
	UBRRXL = baud_setting;

	//UCSRXA = 0; // clear error flags, disable U2X and MPCM

	stdout = &mystdout;

}
