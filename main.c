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


#define IR_COM_0		(0)
#define IR_COM_1		(1)
#define IR_COM_2		(2)
#define IR_COM_3		(3)
#define IR_COM_4		(4)
#define IR_COM_5		(5)
#define IR_COM_6		(6)
#define IR_COM_7		(7)
#define IR_COM_8		(8)
#define IR_COM_9		(9)
#define IR_COM_PLUS		(10)
#define IR_COM_MINUS	(11)
#define IR_COM_ON		(12)
#define IR_COM_PP		(14)
#define IR_COM_RIGHT	(16)
#define IR_COM_LEFT		(17)
#define IR_COM_UP		(32)
#define IR_COM_DOWN		(33)
#define IR_COM_YELLOW	(50)
#define IR_COM_BLUE		(52)
#define IR_COM_GREEN	(54)
#define IR_COM_RED		(55)
#define IR_COM_AV		(56)
#define IR_COM_OK		(59)

#define IR_COM_CROSS	(45)
#define IR_COM_TV		(60)

#define IR_COM_PIP		(0x26)
#define IR_COM_ESC		(0x3F) // Vitiaz - esc  VDS - tv

//VSD

#define IR_COM_VSD_PtoP		(34)// dot
#define IR_COM_VSD_MENU		(48)
#define IR_COM_VSD_DOUBLE_LEFT		(21)
#define IR_COM_VSD_DOUBLE_RIGHT		(22)

extern void uart_init();
extern void dmdp10_Init();


extern Font_t Font[];
char val = 0;
//int val2 = 0;

extern void GLClock_ShowTemp(unsigned char val, unsigned char sign);
extern void GLClock_ShowClock(unsigned char hour, unsigned char min, unsigned char dot);
extern void ds18x20_SelfTest();
extern unsigned char ds18x20_GetHight();
extern unsigned char ds18x20_GetLow();
extern unsigned char ds18x20_Sign();

extern void rc5Init();
extern unsigned char  rc5GetCmd(unsigned char  *outPtr);


void Task_Temp()
{
	ds18x20_ReadTemp();
	memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
	GLClock_ShowTemp(ds18x20_GetHight(), ds18x20_Sign);
	val = ds18x20_GetHight();
	tx_print_usart("T  ");
			tx_hexprint_usart(&val, 1);
	//DEBUG_PRINTF("\n\r Temp %d.%d", ds18x20_GetHight(), ds18x20_GetLow());
}

void Task_Clock()
{
	//ds1307_startstop(1);
}

#define GSC_CMD_ENTERMENU	0xF0
#define GSC_CMD_EXITMENU	0xE0
#define GSC_CMD_DIGIT		0x10
#define GSC_CMD_INC			0x20
#define GSC_CMD_DEC			0x30

char Task_RC5()
{
	unsigned char rc5cmd;
	unsigned char ret = 0;

	if(rc5GetCmd(&rc5cmd))
		{
			switch(rc5cmd)
				{
					case IR_COM_0:
					case IR_COM_1:
					case IR_COM_2:
					case IR_COM_3:
					case IR_COM_4:
					case IR_COM_5:
					case IR_COM_6:
					case IR_COM_7:
					case IR_COM_8:
					case IR_COM_9:		ret = GSC_CMD_DIGIT | rc5cmd;	break;

					case IR_COM_ESC:	ret = GSC_CMD_EXITMENU;			break;

					case IR_COM_AV:					break;


					case IR_COM_ON:					break;
					case IR_COM_RIGHT:				break;
					case IR_COM_LEFT:				break;
					case IR_COM_UP:					break;
					case IR_COM_DOWN:				break;
					case IR_COM_OK:					break;

					case IR_COM_TV:
							//ds1307_startstop(1);
							ds18x20_ReadTemp();
						break;

					default:
						break;
				}
		}

	return ret;
}

void Task_Main()
{
	static char state = 0;
	static char cmd = 0;

	cmd  = Task_RC5();
	if(cmd == GSC_CMD_ENTERMENU)
	{
		state = 1;
	}

	switch(state)
	{
		case 0:

			break;
		case 1:

			break;

		default:

			break;
	}

}

int main(void) {

	unsigned char i = 0;

	uart_init();

	//DEBUG_PRINTF("begin \n\r");
	//DEBUG_PRINTF_SOFT("begin 2 \n\r");

	ds18x20_ReadTemp();
	dmdp10_Init();
	//ds1307_init();
	rc5Init();
	memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));

	sei();
	//GLClock_ShowClock(12, i++, 1);
	GLClock_ShowTemp(55, 0);
	while (1) {

		tx_print_usart("C  ");
		tx_hexprint_usart(&i, 1);
		_delay_ms(500);


		//Task_Temp();
		_delay_ms(1500);
		//memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
		GLClock_ShowClock(88, 00, 1);


	}

}
