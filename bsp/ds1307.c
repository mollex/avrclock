/*****************************************************************************/
/**
* ds1307.c
*
*  Created on: 25.07.2013
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

#include "i2c.h"
/************************** Constant Definitions ****************************/
#define DS1307_ADDR (0x68<<1)
/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes ******************************/
/**<
 * **************************************************************************
 * @brief	Function interrupt UART recv
 *
 * @param 	None.
 * @return  None.
 ***************************************************************************/
unsigned char ds1307_read(unsigned char addr)
{
  uint8_t sec;

  TWIM_Start(DS1307_ADDR, TW_WRITE);
  TWIM_Write(0x00);
  TWIM_Stop();

  TWIM_Start(DS1307_ADDR, TW_READ);
  sec =  TWIM_ReadAck();
  TWIM_ReadNack();

  TWIM_Start(DS1307_ADDR, TW_WRITE);
  TWIM_Write(0x00);
  if(bit)
  {
	  TWIM_Write(sec & 0x7F);
  }else
  {
	  TWIM_Write(sec | 0x80); //hold
  }
  TWIM_Stop();

  return;
}
/**<
 * **************************************************************************
 * @brief	Function send char by different interface
 *
 * @param 	b. 	char send value
 * @return  None.
 ***************************************************************************/


/**<
 * **************************************************************************
 * @brief	Function send then get char by different interface
 *
 * @param 	b. 	char send value
 * @return  Char.	Receive value
 ***************************************************************************/
void ds1307_startstop(char bit)
{
  uint8_t sec;

  TWIM_Start(DS1307_ADDR, TW_WRITE);
  TWIM_Write(0x00);
  TWIM_Stop();

  TWIM_Start(DS1307_ADDR, TW_READ);
  sec =  TWIM_ReadAck();
  TWIM_ReadNack();

  TWIM_Start(DS1307_ADDR, TW_WRITE);
  TWIM_Write(0x00);
  if(bit)
  {
	  TWIM_Write(sec & 0x7F);
  }else
  {
	  TWIM_Write(sec | 0x80); //hold
  }
  TWIM_Stop();
 /*
  //get second and CH bit
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDR, 1);
  sec = Wire.read();
  Wire.read();

  //set second and clear CH bit
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(byte(0x00));
  Wire.write(sec & 0x7F);
  Wire.endTransmission();*/

  return;
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
		TWIM_Init (100000);
}
