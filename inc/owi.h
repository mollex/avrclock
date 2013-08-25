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
* @file owi.h
*
* Put short file description here  !
*
* 	Created on: 08.11.2012
*   	Author: mollex
*
******************************************************************************/

#ifndef OWI_H
#define OWI_H
/***************************** Include Files *******************************/
#include <stdint.h>
#include <avr/io.h>
/************************** Constant Definitions ****************************/

// Port configuration registers for 1-Wire buses.
#define     OWI_PORT        PORTB   //!< 1-Wire PORT Data register.
#define     OWI_PIN         PINB    //!< 1-Wire Input pin register.
#define     OWI_DDR         DDRB    //!< 1-Wire Data direction register.
// Pin bitmasks.
#define     OWI_PIN_0       0x01
#define     OWI_PIN_1       0x02
#define     OWI_PIN_2       0x04
#define     OWI_PIN_3       0x08
#define     OWI_PIN_4       0x10
#define     OWI_PIN_5       0x20
#define     OWI_PIN_6       0x40
#define     OWI_PIN_7       0x80
#define 	DS18B20_PIN   	OWI_PIN_0
// Timing parameters
#define     CPU_FREQUENCY    CPU_CLOCK
#define     OWI_DELAY_OFFSET_CYCLES    13   //!< Timing delay when pulling bus low and releasing bus.
// Bit timing delays in clock cycles = us.
#define     OWI_DELAY_A_STD_MODE    6
#define     OWI_DELAY_B_STD_MODE    64
#define     OWI_DELAY_C_STD_MODE    60
#define     OWI_DELAY_D_STD_MODE    10
#define     OWI_DELAY_E_STD_MODE    9
#define     OWI_DELAY_F_STD_MODE    55
#define     OWI_DELAY_G_STD_MODE    0
#define     OWI_DELAY_H_STD_MODE    480     //Импульс сброса ("Reset Pulse" или просто RESET)
#define     OWI_DELAY_I_STD_MODE    50      //Ожидание  окончания разряда емкости линии
#define     OWI_DELAY_J_STD_MODE    430     //Ожидание  присутствия  "Presence pulse"

// This macro sets the direction of the 1-Wire pin(s) to output and
//  pull the line(s) low.
#define OWI_PULL_BUS_LOW(bitMask) \
		   OWI_DDR |= bitMask; \
		   OWI_PORT &= ~bitMask;

// Set 1-Wire pin(s) to input mode. No internal pull-up enabled.
#define OWI_RELEASE_BUS(bitMask) \
			OWI_DDR &= ~bitMask; \
			OWI_PORT |= bitMask;    //  //OWI_PORT &= ~bitMask;

/************** Macros 1-WIRE ROM commands ***********************************/
#define     OWI_ROM_READ    0x33    //!< READ ROM command code.
#define     OWI_ROM_SKIP    0xcc    //!< SKIP ROM command code.
#define     OWI_ROM_MATCH   0x55    //!< MATCH ROM command code.
#define     OWI_ROM_SEARCH  0xf0    //!< SEARCH ROM command code.

/************** Macros 1-WIRE Return codes ***********************************/
#define     OWI_ROM_SEARCH_FINISHED     0x00    //!< Search finished return code.
#define     OWI_ROM_SEARCH_FAILED       0xff    //!< Search failed return code.

/************** Macros DS18B20  DEFINES **************************************/
#define ds18b20_rev					3

// function commands
#define DS18B20_CONVERT_TEMP		0x44
#define DS18B20_WRITE_SCRATCHPAD	0x4E
#define DS18B20_READ_SCRATCHPAD		0xBE
#define DS18B20_COPY_SCRATCHPAD		0x48
#define DS18B20_RECALL_E2			0xB8
#define DS18B20_READ_POWER			0xB4

// resolution min and max
#define DS18B20_RES_MIN				9
#define DS18B20_RES_MAX				12

// no alarm values for high and low
#define DS18B20_NO_ALARM_LOW		-56		// min temp read is -55C
#define DS18B20_NO_ALARM_HIGH		126		// max temp read is 125C

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/
//  Инициализация шины 1-wire
	void OWI_Init(unsigned char pins);
//  Выдача в линию импульса сброса
	unsigned char OWI_DetectPresence(unsigned char pins);
	unsigned char OWI_dallasCRC(unsigned char i);
//  Запись одного байта данных
	void OWI_SendByte(unsigned char data, unsigned char pins);
//  Чтение одного байта данных
	unsigned char OWI_ReceiveByte(unsigned char pin);
//  Игнорировать адрес - используется для обращения к единственному устройству на шине,
//  при этом адрес устройства игнорируется (можно обращаться к неизвестному устройству)
	void OWI_SkipRom(unsigned char pins);
//  Чтение адреса устройства - используется для определения адреса единственного устройства на шине
	void OWI_ReadRom(unsigned char * romValue, unsigned char pin);
//  Выбор адреса - используется для обращения к конкретному адресу устройства из многих подключенных
	void OWI_MatchRom(unsigned char * romValue, unsigned char pins);
	unsigned char OWI_dallasCRCBuff(unsigned char *ptr, int size);

#endif /* GL_H_ */
