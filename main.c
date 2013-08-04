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
extern void GL_Test();
extern void ht1632c_Init();
extern void dmdp10_Init();
extern void dmdp10_Scan();

extern void GL_DrawNumber(Font_t *font, uint16_t x0, uint16_t y0, uint32_t num, uint8_t colour);

extern Font_t Font[];
int val = 0;
int val2 = 0;



extern void ds18x20_SelfTest();
extern void ds18x20_SelfTest();
extern unsigned char ds18x20_GetHight();
extern unsigned char ds18x20_GetLow();
extern unsigned char ds18x20_Sign();
extern void rc5Init();

int main(void) {

	unsigned char rc5cmd;
	unsigned char i = 0;
	uart_init();

	DEBUG_PRINTF("begin \n\r");

	dmdp10_Init();
	//ds1307_init();
	//rc5Init();
	//memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));

		sei();


		/*GL_DrawChar(&Font[0], 0, 0, '0', 0);
		GL_DrawChar(&Font[0], 8, 0, '1', 0);

		GL_DrawChar(&Font[1], 16, 0, '1', 0);
		GL_DrawChar(&Font[1], 40, 0, '1', 0);*/
	while (1) {

		//DEBUG_PRINTF_SOFT("begin 2 \n\r");
		printf("C  %d\n\r", i++);
		_delay_ms(1000);

		//ds1307_startstop(1);

		//ds18x20_ReadTemp();

		//DEBUG_PRINTF("\n\r Temp %d.%d", ds18x20_GetHight(), ds18x20_GetLow());

		/*if(rc5GetCmd(&rc5cmd))
		{
			//ds1307_startstop(1);
			ds18x20_ReadTemp();
		}*/
			//val = 0;
			GLClock_SetHour(&Font[0], val++);
			GLClock_SetMinutes(&Font[0], 0);
			GLClock_SetDots(val & 0x1);
			//GL_DrawNumber(&Font[1], 1, 2,val2++,1);
			//GL_DrawNumber(&Font[0], 0, 0,2222,1);
			//GL_DrawNumber(&Font[0], 32, 5,3333,1);
	}


}
