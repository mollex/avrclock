/*******************************************************
 Author:					Manfred Langemann
 mailto:					Manfred.Langemann ät t-online.de
 Begin of project:			04.01.2008
 Latest version generated:	04.01.2008
 Filename:					i2c.h
 Description:    			TWI Master functions include file

 ********************************************************/
#ifndef _I2C_H
#define _I2C_H

#include <util/twi.h>

char TWIM_Init(uint32_t TWI_Bitrate);
char TWIM_Start(uint8_t address, uint8_t TWIM_Type);
extern void TWIM_Stop(void);
char TWIM_Write(uint8_t byte);
char TWIM_ReadAck(void);
char TWIM_ReadNack(void);

#endif
