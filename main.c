/*
 * LedForex2012.c
 *
 * Created: 16.11.2012 13:59:09
 *  Author: mollex
 */

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "gl.h"
#include "font.h"
#include "owi.h"
#include "debug.h"

extern void uart_init();
extern void dmdp10_Init();


extern Font_t Font[];
//int val = 0;
//int val2 = 0;



extern void ds18x20_SelfTest();
extern void ds18x20_SelfTest();
extern unsigned char ds18x20_GetHight();
extern unsigned char ds18x20_GetLow();
extern unsigned char ds18x20_Sign();
extern void rc5Init();



void Task_Temp()
{
	//ds18x20_ReadTemp();
	//DEBUG_PRINTF("\n\r Temp %d.%d", ds18x20_GetHight(), ds18x20_GetLow());
}

void Task_Clock()
{
	//ds1307_startstop(1);
}

void Task_RC5()
{
	/*if(rc5GetCmd(&rc5cmd))
		{
			//ds1307_startstop(1);
			ds18x20_ReadTemp();
		}*/
}



int main(void) {

	//unsigned char rc5cmd;
	//unsigned char i = 0;
	uart_init();

	//DEBUG_PRINTF("begin \n\r");
	//DEBUG_PRINTF_SOFT("begin 2 \n\r");


	//dmdp10_Init();
	//ds1307_init();
	//rc5Init();
	//memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
	sei();



	while (1) {

	//	printf("C  %d\n\r", i++);
		_delay_ms(500);


		/*val = 0;
		GLClock_SetHour(&Font[0], val++);
		GLClock_SetMinutes(&Font[0], 0);
		GLClock_SetDots(val & 0x1);
*/
	}

}
