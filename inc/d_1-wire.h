#ifndef ONE_WIRE_H
#define ONE_WIRE_H
//*****************************************************************************
// File Name	: ds18b20.c
// Title		: Dallas 1-Wire DS18B20 Temperature Sensor Library
// Revision		: 3
// Notes		: 
// Target MCU	: Atmel AVR series
// Editor Tabs	: 4
// 
// Revision History:
// When			Who			Rev		Description of change
// -----------	-----------	-------	-----------------------
// 28-May-2009	Korevko A.I.      	Added Print
//*****************************************************************************/


#include <avr/io.h>
/*****************************************************************************
*
*    Макросы
*
******************************************************************************/

/************** Macros 1-WIRE INTERFACE **************************************/

// Port configuration registers for 1-Wire buses.
#define     OWI_PORT        PORTC   //!< 1-Wire PORT Data register.
#define     OWI_PIN         PINC    //!< 1-Wire Input pin register.
#define     OWI_DDR         DDRC    //!< 1-Wire Data direction register.
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

/* DS18X20 specific values (see datasheet) */
#define DS18S20_FAMILY_CODE       0x10
#define DS18B20_FAMILY_CODE       0x28
#define DS1822_FAMILY_CODE        0x22

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

/*****************************************************************************
*
*    Переменные глобальные
*
******************************************************************************/


//----- Typedefs --------------------------------------------------------------

// typedef for the rom IDs
// done so we can access the entire id or each individual byte
typedef struct
{
	unsigned char find;
	unsigned char temperature;
	unsigned char byte[8];
} Dallas_rom_id_t;

Dallas_rom_id_t     Dallas_rom_id;

/*****************************************************************************
*
*    Функции
*
******************************************************************************/

//  Инициализация шины 1-wire
    //void OWI_Init(unsigned char pins);
//  Выдача в линию импульса сброса
    //unsigned char OWI_DetectPresence(unsigned char pins);

//----------------------------------------------------------------------------

//  Запись одного байта данных
    //inline void OWI_SendByte(unsigned char data, unsigned char pins);
//  Чтение одного байта данных
    //inline unsigned char OWI_ReceiveByte(unsigned char pin);
//  Игнорировать адрес - используется для обращения к единственному устройству на шине, 
//  при этом адрес устройства игнорируется (можно обращаться к неизвестному устройству)
    //void OWI_SkipRom(unsigned char pins);
//  Чтение адреса устройства - используется для определения адреса единственного устройства на шине
    //void OWI_ReadRom(unsigned char * romValue, unsigned char pin);
//  Выбор адреса - используется для обращения к конкретному адресу устройства из многих подключенных
    //void OWI_MatchRom(unsigned char * romValue, unsigned char pins);

//-----------------------------------------------------------------------------
//  initializes the dallas 1-wire bus
//  unsigned char ds18b20Init(unsigned char pins);
//  Start the conversion for the given device
//  void ds18b20Start(unsigned char pins);
//-----------------------------------------------------------------------------
    void ds18b20_SelfTest();
	void ds18b20_ReadTemp();
//-----------------------------------------------------------------------------
#endif
