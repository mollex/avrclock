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
#include <avr/wdt.h>

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
unsigned char _text = 0;

char Task_Temp(char count)
{
	char ret = 1;

	//tx_print_usart("count ");	tx_hexprint_usart(&count, 1);
	if(count == 0)
	{
		tx_print_usart("\n\r Read Temp ");
		//memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
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


	if(count == 0)
	{
		tx_print_usart("\n\r Clock Update ");
		timedots= 1;
		ds1307_update();
		GLClock_ShowClock(ds1307_gethour(), ds1307_getmin() , timedots);


		ds1307_adjust();

	}else if(_count < 60)
	{
		if((_count % 5) == 0)
		{
			GLClock_ShowClock(ds1307_gethour(), ds1307_getmin() , ++timedots & 0x01);
		}
	}else
	{
		ret = 0;
	}

	return ret;
}

char Task_Text(char count)
{
	char ret = 1;

	if(_text == 0) ret = 0;

	if(count == 0)
	{
		tx_print_usart("\n\r Text Update ");
		if(_text == IR_COM_RED)GLClock_Phrase2(0);
		if(_text == IR_COM_GREEN)GLClock_Phrase3(0);
		if(_text == IR_COM_BLUE)GLClock_Phrase4(0);
		if(_text == IR_COM_YELLOW)GLClock_Phrase5(0);

	}else if(_count == 15)
	{
		memset(_VideoBuf.vbuff, 0x00, sizeof(_VideoBuf.vbuff));
		_delay_ms(300);
			if(_text == IR_COM_RED)GLClock_Phrase2(63);
			if(_text == IR_COM_GREEN)GLClock_Phrase3(63);
			if(_text == IR_COM_BLUE)GLClock_Phrase4(63);
			if(_text == IR_COM_YELLOW)GLClock_Phrase5(63);
		_delay_ms(300);
		memset(_VideoBuf.vbuff, 0x00, sizeof(_VideoBuf.vbuff));
		_delay_ms(300);
			if(_text == IR_COM_RED)GLClock_Phrase2(63);
			if(_text == IR_COM_GREEN)GLClock_Phrase3(63);
			if(_text == IR_COM_BLUE)GLClock_Phrase4(63);
			if(_text == IR_COM_YELLOW)GLClock_Phrase5(63);

	}else if(_count < 25)
	{

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
		_delay_ms(200);
		isrc5 = 1;
		if(rc5cmd == IR_COM_VSD_MENU)
		{
			state = 0xF0;

		}else if(rc5cmd == IR_COM_VSD_PtoP)
		{
			state = 0xE0;
		}
		else if(rc5cmd == IR_COM_RED)
		{
			//GLClock_Phrase2(0);
			state = 0x2;
			_count = 0;
			_text = rc5cmd;

		}else if(rc5cmd == IR_COM_GREEN)
		{
			//GLClock_Phrase3();
			state = 0x2;
			_count = 0;
			_text = rc5cmd;

		}else if(rc5cmd == IR_COM_BLUE)
		{
			//GLClock_Phrase4();
			state = 0x2;
			_count = 0;
			_text = rc5cmd;
		}else if(rc5cmd == IR_COM_YELLOW)
		{
			//GLClock_Phrase5();
			state = 0x2;
			_count = 0;
			_text = rc5cmd;
		}
		else if(rc5cmd == IR_COM_ON)
		{
			state = 0;
			_count = 0;
			_text = 0;
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
		case 2:
			if(Task_Text(_count++) == 0)
			{
				state++;
				_count = 0;
			}
		break;
		case 0xE0:
			if(isrc5)
			{
				if(GLClock_SetClockCorrect(rc5cmd) == 0){
					state = 0xFF;
					_count = 0;
				}
			}
			break;
		case 0xF0:
			if(isrc5)
			{
				if(GLClock_SetClockSetting(rc5cmd)==0){
					state = 0xFF;
					_count = 0;
				}
			}
			break;
		case 0xF1:

			break;
		default:
			state = 0;
			break;
	}

	rc5GetCmd(&rc5cmd);
}


int main(void) {

	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;

	_delay_ms(500);

	uart_init();
	dmdp10_Init();
	GLClock_Phrase1();
	ds1307_init();
	ds18x20_ReadTemp();
	ds18x20_ReadTemp();
	rc5Init();

	wdt_reset();
	wdt_enable(WDTO_120MS);



	sei();

	tx_print_usart("\n\r GS Clock v3.02 ");

	while (1) {

		//tx_print_usart("\n\r C  ");	tx_hexprint_usart(&(_count), 1);

		//GLClock_Phrase2();
	//	_delay_ms(1000);
		//GLClock_Phrase6(GL_FONT_CONSOLAS);
	//	memset(_VideoBuf.vbuff, 0x00, sizeof(_VideoBuf.vbuff));
		_delay_ms(100);

		Task_Main();
	}
}
