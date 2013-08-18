/*
 * LedForex2012.c
 *
 * Created: 16.11.2012 13:59:09
 *  Author: mollex
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "gl.h"
#include "font.h"
#include "owi.h"
#include "debug.h"
#include "rc5.h"


extern void uart_init();
extern void dmdp10_Init();

extern void ds18x20_ReadTemp();
extern unsigned char ds18x20_GetHight();
extern unsigned char ds18x20_GetLow();
extern unsigned char ds18x20_Sign();

extern void ds1307_init();
extern void ds1307_update();
extern unsigned char ds1307_getsec();
extern unsigned char ds1307_getmin();
extern unsigned char ds1307_gethour();
extern void ds1307_setTime(unsigned char hour, unsigned char min);

unsigned char _val = 0;
unsigned char _count = 0;

char Task_Temp()
{
	static unsigned char state = 0;

	tx_print_usart("state ");	tx_hexprint_usart(&state, 1);

	switch(state)
	{
		case 0:
			state++;
			break;
		case 1:
			state++;
			memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
			GLClock_ShowTemp(ds18x20_GetHight(), ds18x20_Sign());
			_val = ds18x20_GetHight();
			//tx_print_usart("T  ");	tx_hexprint_usart(&_val, 1);
			break;
		case 2:
			if(_count > 20)
			{
				state++;
			}
			break;
		case 3:
			ds18x20_ReadTemp();
			state++;
			break;
		default:
			state = 0;
			break;
	}
	return state;
}

char Task_Clock()
{
	static unsigned char hour;
	static unsigned char min;
	static unsigned char state = 0;
	static unsigned char timeshow= 0;

	switch(state)
	{
		case 0:
			state++;
			break;
		case 1:
			ds1307_update();
			hour = ds1307_gethour();
			min = ds1307_getmin();
			memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
			GLClock_ShowClock(hour, min , 1);

			_count = 0;
			timeshow= 0;
			state++;

			break;
		case 2:
			if(_count > 5)
			{
				_count = 0;
				GLClock_SetDots(timeshow & 0x01);
				if(timeshow++ > 7)state = 0xFF;
			}
			break;

		default:
			state = 0;
			break;
	}
	return state;
}

void Task_Main()
{
	static unsigned char state = 0;
	static unsigned char rc5cmd = 0;

	char isrc5 = 0;

	if(rc5GetCmd(&rc5cmd))
	{
		isrc5 = 1;
		if(rc5cmd == IR_COM_VSD_MENU)
		{
			state = 2;

		}else if(rc5cmd == IR_COM_ESC)
		{
			state = 0;
		}
	}

	switch(state)
	{
		case 0:

			if(Task_Clock() == 0) state++;
			break;
		case 1:
			if(Task_Temp() == 0) state+=0xF0;
			break;
		case 2:
			if(isrc5)
			{
				memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));

				if(GLClock_SetClockSetting(rc5cmd)==0){state+=0xF0; _delay_ms(500);}
			}

			break;
		default:
			state = 0;
			break;
	}
}

int main(void) {

	_delay_ms(300);

	uart_init();
	ds18x20_ReadTemp();
	dmdp10_Init();
	ds1307_init();
	rc5Init();

	sei();

	while (1) {

		_count++;

		tx_print_usart("\n\r C  ");	tx_hexprint_usart(&_count, 1);

		_delay_ms(100);

		//ds1307_update();
		Task_Main();
	}
}
