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
*****************************************************************************
/*****************************************************************************/
/**
* @file softusart.c
*
* Put short file description here  !
*
* 	Created on: 29.01.2013
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
//#include "inc.h"
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


/************************** Constant Definitions ****************************/
#define CR_TAB "\n\t"
#define STOP_BITS 1

#define bvalue 135	//61
#define SWUART_PORT PORTC	//TX Port
#define SWUART_DDR  DDRC	//TX Port
#define SWUART_PIN	3		//TX Pin

/*
b-values for 16 MHz
BaudRate   	Cycles required   	b-value		Error %
2400      	6667          		(2) 1107    0
4800      	3333          		(2) 552     0
9600      	1667          		(2) 274     0
14400      	1111         		181         0,2
19200      	833            		135         0
28800      	556            		89         	0,3
57600      	278            		42         	1
115200      139            		19         	1,4
*/
/*
b-values for 8 MHz
BaudRate   	Cycles required   	b-value		Error %
2400      	6667          		()     		0
4800      	3333          		()      	0
9600      	1667          		() 		    0
14400      	1111         		         	0,2
19200      	833            		61         	0		(61-wbus good)
28800      	556            		         	0,3
57600      	278            		23         	1
115200      139            		         	1,4
*/
/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/


void suart_Init()
{
}

void txd (char value)
{
   uint8_t bitcnt = 1+8+STOP_BITS;
   uint8_t delay = bvalue;	//see softuart.h
   SWUART_DDR  |= (1<<SWUART_PIN);
   value = ~value;

   cli();

   __asm__ __volatile__(

      "      sec             ; Start bit           " CR_TAB
      "0:    brcc 1f              ; If carry set   " CR_TAB
      "      cbi   %[port],%[pad] ; send a '0'     " CR_TAB
      "      rjmp 2f              ; else           " CR_TAB

      "1:    sbi   %[port],%[pad] ; send a '1'     " CR_TAB
      "      nop"                                    CR_TAB

      "2:    %~call bit_delay_%=  ; One bit delay  " CR_TAB
      "      %~call bit_delay_%="                    CR_TAB

      "      lsr   %[value]   ; Get next bit        " CR_TAB
      "      dec   %[bitcnt] ; If not all bit sent " CR_TAB
      "      brne 0b         ; send next           " CR_TAB
      "      rjmp 5f         ; else: done          " CR_TAB
                                                     CR_TAB
      "bit_delay_%=:"                                CR_TAB
      "      mov   __zero_reg__, %[delay]"           CR_TAB
      "4:    dec   __zero_reg__"                     CR_TAB
      "      brne 4b"                                CR_TAB
      "      ret"                                    CR_TAB
      "5:"                                           CR_TAB

      : [bitcnt] "=r" (bitcnt), [value] "=r" (value)
      : "1" (value), "0" (bitcnt), [delay] "r" (delay), [port] "M" (_SFR_IO_ADDR(SWUART_PORT)), [pad] "M" (SWUART_PIN)
   );

   SWUART_PORT |= (1<<SWUART_PIN);
   sei();

   _delay_us(500);
}

void tx_print(char *s)
{
	while(*s)
	{
		txd (*s++);
	}
}

void tx_hexprint(char *s, char len)
{
	char b[6] = {'0', 'x', 'q','q', ' ', 0};
	register char r1 = 0;
	register char r2 = 0;
	while(len--)
	{
		r1 = r2 = *s++;
		r1 = r1>>4;
		r2 &= 0x0F;
		b[2] = r1 + ((r1>9) ? 0x57 : 0x30);
 		b[3] = r2 + ((r2>9) ? 0x57 : 0x30);
 		tx_print(b);
	}
	tx_print(" \n\r");
}
