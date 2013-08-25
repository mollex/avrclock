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
extern void ds1307_adjust();
extern unsigned char ds1307_getsec();
extern unsigned char ds1307_getmin();
extern unsigned char ds1307_gethour();
extern void ds1307_setTime(unsigned char hour, unsigned char min);

unsigned char _val = 0;
unsigned char _count = 0;

char Task_Temp(char count)
{
	char ret = 1;

	//tx_print_usart("count ");	tx_hexprint_usart(&count, 1);
	if(count == 0)
	{
		memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
		GLClock_ShowTemp(ds18x20_GetHight(), ds18x20_Sign());
		ds18x20_ReadTemp();
	}else
	{
		if(_count > 20)
		{
			ret = 0;
		}
	}

	return ret;
}

char Task_Clock(char count)
{
	char ret = 1;
	static unsigned char timedots= 1;

	//tx_print_usart("count ");	tx_hexprint_usart(&count, 1);
	if(count == 0)
	{
		timedots= 1;
		ds1307_update();
		memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
		GLClock_ShowClock(ds1307_gethour(), ds1307_getmin() , timedots);

	}else if(_count < 60)
	{
		if((_count % 5) == 0)
		{
			GLClock_SetDots(++timedots & 0x01);
		}
	}else
	{
		ret = 0;
	}

	return ret;
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
			state = 0xF0;

		}else if(rc5cmd == IR_COM_RED)
		{
			memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
			GLClock_Phrase2();
			state = 0xF1;
		}else if(rc5cmd == IR_COM_GREEN)
		{
			memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
			GLClock_Phrase3();
			state = 0xF1;
		}else if(rc5cmd == IR_COM_BLUE)
		{
			memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
			GLClock_Phrase4();
			state = 0xF1;
		}else if(rc5cmd == IR_COM_YELLOW)
		{
			memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
			GLClock_Phrase5();
			state = 0xF1;
		}
		else if(rc5cmd == IR_COM_ON)
		{
			state = 0;
			_count = 0;
		}
	}


	switch(state)
	{
		case 0:
			if(Task_Clock(_count++) == 0)
			{
				state++;
				_count = 0;
			}
			break;
		case 1:
			if(Task_Temp(_count++) == 0)
			{
				state++;
				_count = 0;
			}
			break;

		case 0xF0:
			if(isrc5)
			{
				if(GLClock_SetClockSetting(rc5cmd)==0){
					state = 0;
					_count = 0;
				}
			}
		case 0xF1:

			break;
		default:
			state = 0;
			break;
	}
}

int main(void) {

	_delay_ms(300);

	uart_init();
	dmdp10_Init();
	GLClock_Phrase1();
	ds1307_init();
	ds18x20_ReadTemp();
	ds18x20_ReadTemp();
	rc5Init();

	sei();
	while (1) {

		tx_print_usart("\n\r C  ");	tx_hexprint_usart(&(_count), 1);

		_delay_ms(100);

		Task_Main();
	}
}
