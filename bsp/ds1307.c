/*****************************************************************************/
/**
* ds1307.c
*
*  Created on: 25.07.2013
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

#include "i2c.h"
/************************** Constant Definitions ****************************/
#define DS1307_ADDR (0x68<<1)

#define DS1307_REG_SEC		0
#define DS1307_REG_MIN		1
#define DS1307_REG_HOUR		2
#define DS1307_REG_DOW		3
#define DS1307_REG_DATE		4
#define DS1307_REG_MON		5
#define DS1307_REG_YEAR		6
#define DS1307_REG_CON		7
/**************************** Type Definitions ******************************/
	typedef struct
	{
		unsigned char sec;
		unsigned char min;
		unsigned char hour;

	} DS1307_t;

	DS1307_t     _DS1307;
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes ******************************/
/**<
 * **************************************************************************
 * @brief	Function read
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
unsigned char ds1307_getsec()
{
	return _DS1307.sec;
}
unsigned char ds1307_getmin()
{
	return _DS1307.min;
}
unsigned char ds1307_gethour()
{
	return _DS1307.hour;
}
/**<
 * **************************************************************************
 * @brief	Function read
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
// Convert Decimal to Binary Coded Decimal (BCD)
unsigned char dec2bcd(unsigned char num)
{
  return ((num/10 * 16) + (num % 10));
}
// Convert Binary Coded Decimal (BCD) to Decimal
unsigned char bcd2dec(unsigned char num)
{
  return ((num/16 * 10) + (num % 16));
}
/**<
 * **************************************************************************
 * @brief	Function read
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
unsigned char ds1307_read(unsigned char addr)
{
	unsigned char val;
	TWIM_Start(DS1307_ADDR, TW_WRITE);
	TWIM_Write(addr);
	TWIM_Stop();

	TWIM_Start(DS1307_ADDR, TW_READ);
	val =  TWIM_ReadAck();
	TWIM_ReadNack();
	TWIM_Stop();

	return val;
}
/**<
 * **************************************************************************
 * @brief	Function write
 *
 * @param 	b. 	char send value
 * @return  None.
 ***************************************************************************/
void ds1307_write(unsigned char addr, unsigned char val)
{
  TWIM_Start(DS1307_ADDR, TW_WRITE);
  TWIM_Write(addr);
  TWIM_Write(val);
  TWIM_Stop();
}
/**<
 * **************************************************************************
 * @brief	Function
 *
 * @param 	b.
 * @return  none
 ***************************************************************************/
void ds1307_startstop(char bit)
{
  uint8_t sec;

  sec =  ds1307_read(DS1307_REG_SEC);

  if(bit)
  {
	  ds1307_write(DS1307_REG_SEC, sec & 0x7F);
  }else
  {
	  ds1307_write(DS1307_REG_SEC, sec | 0x80); //hold
  }
}
/**<
 * **************************************************************************
 * @brief	Function
 *
 * @param 	b.
 * @return  none
 ***************************************************************************/
void ds1307_setTime(unsigned char hour, unsigned char min)
{
	if ((hour<24) && (min<60))
	{
		_DS1307.sec =  0;
		_DS1307.min =  min;
		_DS1307.hour = hour;

		ds1307_write(DS1307_REG_SEC, 0);
		ds1307_write(DS1307_REG_MIN, dec2bcd(_DS1307.min));
		ds1307_write(DS1307_REG_HOUR, dec2bcd(_DS1307.hour));
	}
}
/**<
 * **************************************************************************
 * @brief	Function
 *
 * @param 	b.
 * @return  none
 ***************************************************************************/
void ds1307_update()
{
  _DS1307.sec =  bcd2dec(ds1307_read(DS1307_REG_SEC));
  _DS1307.min =  bcd2dec(ds1307_read(DS1307_REG_MIN));
  _DS1307.hour =  ds1307_read(DS1307_REG_HOUR);

 /* tx_print_usart("H  "); tx_hexprint_usart(&_DS1307.hour, 1);
  tx_print_usart("M  "); tx_hexprint_usart(&_DS1307.min, 1);
  tx_print_usart("S  "); tx_hexprint_usart(&_DS1307.sec, 1);*/

  if (_DS1307.hour & (1<<6))
	 _DS1307.hour = (_DS1307.hour & 0xF) + (12 * ((_DS1307.hour & 0x20) >> 5));
  else
	 _DS1307.hour = (_DS1307.hour & 0xF) + (10 * ((_DS1307.hour & 0x30) >> 4));

}
/**<
 * **************************************************************************
 * @brief	Function initializing peripherals
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
void ds1307_init()
{
	// Initiate TWI Master with bitrate of 100000 Hz
	TWIM_Init (50000);

	ds1307_startstop(1);
}
