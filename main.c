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
#include "d_1-wire.h"

extern void uart_init();
extern void GL_Test();
extern void ht1632c_Init();
extern void dmdp10_Init();
extern void dmdp10_Scan();

extern void GL_DrawNumber(Font_t *font, uint16_t x0, uint16_t y0, uint32_t num, uint8_t colour);

extern VideoBuf_t	VideoBuf;
extern Font_t Font[];
int val = 0;
int val2 = 0;

extern void tx_print(char *s);
extern void tx_hexprint(char *s, char len);


int main(void) {
	uart_init();



	printf("begin 1 \n\r");
	tx_print("begin 2 \n\r");

	dmdp10_Init();
	ds1307_init();
	memset(VideoBuf.vbuff, 0x0, sizeof(VideoBuf.vbuff));

		sei();


		/*GL_DrawChar(&Font[0], 0, 0, '0', 0);
		GL_DrawChar(&Font[0], 8, 0, '1', 0);

		GL_DrawChar(&Font[1], 16, 0, '1', 0);
		GL_DrawChar(&Font[1], 40, 0, '1', 0);*/

	while (1) {

		tx_print("begin 2 \n\r");

		_delay_ms(3000);

		//ds1307_startstop(1);

		//ds18b20_SelfTest();
		ds18b20_ReadTemp();

			//val = 0;
			GLClock_SetHour(&Font[2], val++);
			GLClock_SetMinutes(&Font[2], 0);
			GLClock_SetDots(val & 0x1);
			//GL_DrawNumber(&Font[2], 1, 2,val2++,1);
			//GL_DrawNumber(&Font[0], 0, 0,2222,1);
			//GL_DrawNumber(&Font[0], 32, 5,3333,1);
	}


}
