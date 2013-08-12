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
* @file rc5.c
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
#define	RC5_PORT_SET	DDRD
#define	RC5_PORT_IN		PIND
#define	RC5_PIN			PD3			// IR input low active

#define	XTAL		16000000

#define RC5TIME 	1.778e-3		// 1.778msec
//#define PULSE_MIN	(uint8_t)(XTAL / 512 * RC5TIME * 0.4 + 0.5)
//#define PULSE_1_2	(uint8_t)(XTAL / 512 * RC5TIME * 0.8 + 0.5)
//#define PULSE_MAX	(uint8_t)(XTAL / 512 * RC5TIME * 1.2 + 0.5)
//#define PULSE_MIN	(uint8_t)(XTAL / 1024 * RC5TIME * 0.4 + 0.5)
//#define PULSE_1_2	(uint8_t)(XTAL / 1024 * RC5TIME * 0.8 + 0.5)
//#define PULSE_MAX	(uint8_t)(XTAL / 1024 * RC5TIME * 1.2 + 0.5)
#define PULSE_MIN	(uint8_t)(XTAL / 2048 * RC5TIME * 0.4 + 0.5)
#define PULSE_1_2	(uint8_t)(XTAL / 2048 * RC5TIME * 0.8 + 0.5)
#define PULSE_MAX	(uint8_t)(XTAL / 2048 * RC5TIME * 1.2 + 0.5)
/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
uint8_t	rc5_bit;				// bit value
uint8_t	rc5_time;				// count bit time
uint16_t	rc5_tmp;			// shift bits in
uint16_t	rc5_data;			// store result
uint8_t	rccount;				// bit value
/************************** Function Prototypes *****************************/
/**<
 * **************************************************************************
 * @brief	Timer Intr RC-5 Parser
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
ISR (TIMER0_OVF_vect)
{
	PORTC++;
	uint16_t tmp = rc5_tmp;				// for faster access
	char portin;
 // TCNT0 = -2;					// 2 * 256 = 512 cycle
  //TCNT0 = -4;					// 4 * 256 = 1024 cycle
  TCNT0 = -8;					// 8 * 256 = 2048 cycle

 portin = RC5_PORT_IN;
  if( ++rc5_time > PULSE_MAX ){				// count pulse time
    if( !(tmp & 0x4000) && tmp & 0x2000 )	// only if 14 bits received
      rc5_data = tmp;
    tmp = 0;
  }

  if( (rc5_bit ^ portin) & 1<<RC5_PIN ){		// change detect
    rc5_bit = ~rc5_bit;								// 0x00 -> 0xFF -> 0x00
    if( rc5_time < PULSE_MIN )						// to short
      tmp = 0;
    if( !tmp || rc5_time > PULSE_1_2 ){				// start or long pulse time
      if( !(tmp & 0x4000) )							// not to many bits
        tmp <<= 1;									// shift
      if( !(rc5_bit & 1<<RC5_PIN) )					// inverted bit
        tmp |= 1;									// insert new bit
      rc5_time = 0;									// count next pulse time
    }
  }

  rc5_tmp = tmp;

 // dmdp10_Scan();
  //if(rccount++ == 0x2){rccount = 0; dmdp10_Scan();}
}
/**<
 * **************************************************************************
 * @brief	Function initializing
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void rc5Init()
{

	RC5_PORT_SET &=  ~(1<<RC5_PIN);
	PORTD |= (1<<RC5_PIN);


#if defined (__AVR_ATmega8__)

	TCCR0 = 1<<CS02;			//divide by 256
	TIMSK |= 1<<TOIE0;			//enable timer interrupt

#else
		TCCR0B = 1<<CS02;			//divide by 256
		TIMSK0 = 1<<TOIE0;			//enable timer interrupt
#endif
}


typedef struct
{
	union {
		struct {
			uint16_t key 	:6; 	/**< 6 бит команды */
			uint16_t addr	:5; 	/**< 5 бит адреса системы */
			uint16_t tgl 	:1; 	/**< 1 управляющий бит */
			uint16_t start 	:2; 	/**< 2 стартовых бита */
			};
			uint16_t val;
		};
}RC_t;

/**<
 * **************************************************************************
 * @brief	Function parser RC-5 control
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
unsigned char  rc5GetCmd(unsigned char  *outPtr)
{
	RC_t cmd;
	cli();
	cmd.val = rc5_data;			// read two bytes from interrupt !
	rc5_data = 0;
	sei();

	if(cmd.val == 0) return 0;

	/*printf("\n\r ntgl %d", cmd.tgl);
	printf("\n\r naddr %d", cmd.addr);*/
	//printf("\n\r key 0x%x\n\r", cmd.key);

	*outPtr = cmd.key;

	return 1;
}
