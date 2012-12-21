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

#include "gl.h"
#include "font.h"

extern void uart_init();
extern void GL_Test();
extern void ht1632c_Init();
extern void dmdp10_Init();
extern void dmdp10_Scan();

extern void GL_DrawNumber(Font_t *font, uint16_t x0, uint16_t y0, uint32_t num, uint8_t colour);

extern VideoBuf_t	VideoBuf;
extern Font_t Font[];
int main(void) {
	uart_init();

	printf("begin\\n\r");

	dmdp10_Init();

	memset(VideoBuf.vbuff, 0x0, sizeof(VideoBuf.vbuff));
	GL_SetPixel(0, 0, 1);
	GL_SetPixel(2, 2, 1);
	GL_SetPixel(0, 5, 1);

	GL_DrawNumber(&Font[1], 0, 0,1234,1);

	//VideoBuf.vbuff[0][0][0] = 0x11;
	//VideoBuf.vbuff[0][0][1] = 0x22;
	while (1) {

		memset(VideoBuf.vbuff, 0x0, sizeof(VideoBuf.vbuff));
		GL_DrawNumber(&Font[0], 0, 0,1234,1);
		int j = 2000;
		while(j--)
		{
		dmdp10_Scan();
		_delay_ms(1);
		}

		memset(VideoBuf.vbuff, 0x0, sizeof(VideoBuf.vbuff));
		GL_DrawNumber(&Font[1], 0, 5,1284,1);
		 j = 2000;
		while(j--)
		{
		dmdp10_Scan();
		_delay_ms(1);
		}

	}




	//ht1632c_Init();
	//ht1632c_memset(3, 0x00, 0, 64);



	while (1) {
		int i, j;
		//GL_Test();
		/*for (j = 1; j < 4; j++) {
			for (i = 0; i < 64; i++) {
				ht1632c_memset(3, 0x00, 0, 64);
				ht1632c_memset(j, i, 0xFF, 1);
				_delay_ms(50);

			}
		}*/

		/*ht1632c_memset(1, 16, 0xFF, 1);
		_delay_ms(1500);
		uint8_t buff[] = {1,2,3,4,5,6,7,8,9,10};
		ht1632c_sendBuffer8(1, 0, buff, sizeof(buff));

		_delay_ms(1500);*/
		//TODO:: Please write your application code
	}
}
