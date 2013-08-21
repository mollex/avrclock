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
* @file gl.c
*
* Put short file description here  !
*
* 	Created on: Nov 21, 2012
*   	Author: mollex
*
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a    			  First release
*
******************************************************************************/

/****************************** Include Files *******************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "font.h"
#include "gl.h"
#include "rc5.h"
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
extern  FontChar_t segmental_28ptDescriptors[];
extern  unsigned char segmental_28ptBitmaps[];

extern  FontChar_t segoeCondensed_14ptDescriptors[];
extern  unsigned char segoeCondensed_14ptBitmaps[];

// Font information for Courier New 8pt
Font_t _Font[] =
{
	{
		.heightPages = 2, //  Character height
		.pt = 54,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 2, //  Width, in pixels, of space character
		.charInfo = segmental_28ptDescriptors, //  Character descriptor array
		.dataPtr = segmental_28ptBitmaps, //  Character bitmap array
	},
	{
		.heightPages = 2, //  Character height
		.pt = 54,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 1, //  Width, in pixels, of space character
		.charInfo = segoeCondensed_14ptDescriptors, //  Character descriptor array
		.dataPtr = segoeCondensed_14ptBitmaps, //  Character bitmap array
	},
};


VideoBuf_t	_VideoBuf = {

	.xmax = VBUFF_X_MAX,
	.ymax = VBUFF_Y_MAX,
	.xline = VBUFF_X_LINE,
	.yline = VBUFF_Y_LINE,

};
/************************* Function Prototypes *****************************/
extern void ds1307_setTime(unsigned char hour, unsigned char min);
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
/*static void gl_uart()
{
	int xl, yl;
	uint32_t b;

	printf("\f");
	for(yl=0; yl < _VideoBuf.ymax; yl++){
		for(xl=0; xl < _VideoBuf.xline; xl++){
			for(b=0; b < 16; b++){
				if(_VideoBuf.vbuff[yl/16][xl][yl] & (1<<b)) printf("#");
				else printf(".");
			}
		}
		printf("\r\n");
	}

	memset(_VideoBuf.vbuff, 0, sizeof(_VideoBuf.vbuff));
}*/
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
void gl_setpixel(uint16_t x, uint16_t y, int val)
{
	if(x > _VideoBuf.xmax || y > _VideoBuf.ymax)	return;

	uint16_t xline  = x/8;
	uint16_t yline = y/16;
	if(val)
	{
		_VideoBuf.vbuff[yline][xline][y%16] |= (1 << (x%8));
	}
	else
	{
		_VideoBuf.vbuff[yline][xline][y%16] &=  ~(1 << (x%8));
	}
}
void GL_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, char color) {

	uint16_t dy = y1 - y0;
	uint16_t dx = x1 - x0;
	uint16_t stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
	dy <<= 1;                                                  // dy is now 2*dy
	dx <<= 1;                                                  // dx is now 2*dx

	gl_setpixel(x0, y0, color);
	if (dx > dy) {
		int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                                // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;                                    // same as fraction -= 2*dy
			gl_setpixel(x0, y0, color);
		}
	} else {
		int fraction = dx - (dy >> 1);
		while (y0 != y1) {
			if (fraction >= 0) {
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			gl_setpixel(x0, y0, color);
		}
	}
}
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
int GL_DrawChar(unsigned char font, uint16_t x0, uint16_t y0, char ch)
{
	int j, i=0;
	uint16_t val;
	Font_t *fontPtr = &_Font[font];

	int index = ch - '0';

	fontPtr->heightPages = (fontPtr->charInfo[index].widthBits - 1)/ 8 + 1; // height symbol 1 or more byte
	fontPtr->pt = fontPtr->charInfo[index+1].offset - fontPtr->charInfo[index].offset; //size of bytes symbols

	for(j=0; j<fontPtr->pt; j+=fontPtr->heightPages)
	{
		val =  pgm_read_word(&(fontPtr->dataPtr[fontPtr->charInfo[index].offset + j]));
		for(i=0; i<fontPtr->charInfo[index].widthBits; i++)
		{
			//gl_setpixel(x0+i, y0,  fontPtr->dataPtr[fontPtr->charInfo[index].offset + j +  i/8] & (1<<(i%8)));
			gl_setpixel(x0+i, y0, val & (1<<(i)));
		}
		y0++;
	}
	return (i + fontPtr->spacePixels);
}
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *				русские верхний регистр от 0xC0 ... 0xDF
 *				русские нижний регистр от 0xe0...0xFF
 * @return None.
 *
 *****************************************************************************/
void GL_DrawStr(unsigned char font, uint16_t x0, uint16_t y0, char *str)
{
	//tx_print_usart("\n\r Str  ");
	char b;
	do{
		if(*str >= 0xC0)
		{
		b = *str - 0x90 + 10;
		}else
		{
			b = *str;
		}
		x0 += GL_DrawChar(font, x0, y0, b);
		//tx_hexprint_usart(&b, 1);
	}
	while(*(++str));
}
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
void GL_DrawDots4(uint16_t x0, uint16_t y0, char val)
{
	gl_setpixel(x0, y0, val);
	gl_setpixel(++x0, y0, val);
	gl_setpixel(x0, ++y0, val);
	gl_setpixel(--x0, y0, val);
}
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
void GLClock_Phrase1()
{
	GL_DrawStr(GL_FONT_SEGOE14, 8, 8, "ЗАГРУЗ");
	GL_DrawDots4(60, 17, 1);
}
void GLClock_Phrase2()
{
	GL_DrawStr(GL_FONT_SEGOE14, 21, 1, "ТЕХ");
	GL_DrawDots4(47, 12, 1);
	GL_DrawStr(GL_FONT_SEGOE14, 3, 16, "ПЕРЕРЫВ");
}
void GLClock_Phrase3()
{
	GL_DrawStr(GL_FONT_SEGOE14, 16, 1, "СЛИВ");
	GL_DrawStr(GL_FONT_SEGOE14, 0, 16, "Т0ПЛИВА");
	//GL_DrawDots4(58, 27, 1);
}
void GLClock_Phrase4()
{
	GL_DrawStr(GL_FONT_SEGOE14, 0, 2, "СПАСИБ0");
	//GL_DrawDots4(60, 11, 1);
}
void GLClock_Phrase5()
{
	GL_DrawStr(GL_FONT_SEGOE14, 3, 1, "ЗИМНИЙ");
	GL_DrawStr(GL_FONT_SEGOE14, 7, 16, "ДИЗЕЛЬ");
}
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
void GLClock_SetHour(unsigned char font, char val)
{
	char hight = val/10 + '0';
	char low = val%10 + '0';

	GL_DrawChar(font, 0, 2, hight);
	GL_DrawChar(font, 16, 2, low);

}

void GLClock_SetMinutes(unsigned char font, char val)
{
	char hight = val/10 + '0';
	char low = val%10 + '0';

	GL_DrawChar(font, 34, 2, hight);
	GL_DrawChar(font, 50, 2, low);
}

void GLClock_SetDots(char val)
{
	GL_DrawLine(31, 8, 31, 10, val);
	GL_DrawLine(32, 8, 32, 10, val);
	GL_DrawLine(31, 21, 31, 23, val);
	GL_DrawLine(32, 21, 32, 23, val);
}
void GLClock_ShowClock(unsigned char hour, unsigned char min, unsigned char dot)
{
	GLClock_SetHour(GL_FONT_SEGMENTAL28, hour);
	GLClock_SetMinutes(GL_FONT_SEGMENTAL28, min);
	GLClock_SetDots(dot);
}
void GLClock_SetCursor(unsigned int x0, unsigned int y0)
{
	GL_DrawLine(x0, y0+2, x0 + 12, y0+2, 1);
	GL_DrawLine(x0+2, y0+1, x0 + 10, y0+1, 1);
	GL_DrawLine(x0+4, y0, x0 + 8, y0, 1);
	GL_DrawLine(x0+5, y0, x0 + 7, y0, 1);
}
char GLClock_SetClockSetting(unsigned char cmd)
{
	static unsigned char val[4];
	static int indx;
	char ret = 1;

	if(cmd == IR_COM_VSD_MENU)
	{
		val[0] = val[1] = val[2] = val[3] = 0xFF;
		indx = 0;
		memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
	}
	else if(cmd < 10)
	{
		if(indx == 0)
		{
			if(cmd <= 2) val[indx++] = cmd;
		}
		else if(indx == 1)
		{
			if(val[0] == 2)
			{
				if(cmd <= 3) val[indx++] = cmd;
			}else
			{
				if(cmd <= 9) val[indx++] = cmd;
			}
		}
		else if(indx == 2)
		{
			if(cmd <= 5) val[indx++] = cmd;
		}
		else if(indx == 3)
		{
			if(cmd <= 9) val[indx++] = cmd;
			ret = 0;

			val[0] = val[0] * 10 + val[1];
			val[2] = val[2] * 10 + val[3];
			ds1307_setTime(val[0], val[2]);
		}
		else if(indx > 3)
		{
			ret = 0;
		}
	}

	GLClock_SetDots(1);
	if(val[0] == 0xFF)GLClock_SetCursor(1,26); else GL_DrawChar(GL_FONT_SEGMENTAL28, 0, 2, val[0] + '0');
	if(val[1] == 0xFF)GLClock_SetCursor(17,26);else GL_DrawChar(GL_FONT_SEGMENTAL28, 16, 2, val[1] + '0');
	if(val[2] == 0xFF)GLClock_SetCursor(33,26);else GL_DrawChar(GL_FONT_SEGMENTAL28, 34, 2, val[2] + '0');
	if(val[3] == 0xFF)GLClock_SetCursor(51,26);else GL_DrawChar(GL_FONT_SEGMENTAL28, 50, 2, val[3] + '0');

	return ret;
}
/****************************************************************************/
/**
 * @brief	 	Функция
 *
 * @param None 	Аргумент
 *
 * @return None.
 *
 *****************************************************************************/
void GLClock_SetTemp(unsigned char font, unsigned char val, unsigned char sign)
{
	char hight = val/10 + '0';
	char low = val%10 + '0';

	GL_DrawChar(font, 11, 2, hight);
	GL_DrawChar(font, 28, 2, low);
	GL_DrawChar(font, 50, 2, 'C');

	GL_DrawLine(45, 3, 47, 3, 1);
	GL_DrawLine(45, 8, 47, 8, 1);
	GL_DrawLine(44, 4, 44, 7, 1);
	GL_DrawLine(48, 4, 48, 7, 1);

	GL_DrawLine(0, 15, 9, 15, 1);
	GL_DrawLine(0, 16, 9, 16, 1);
	if(sign == 0)
	{
		GL_DrawLine(4, 11, 4, 20, 1);
		GL_DrawLine(5, 11, 5, 20, 1);
	}
}

void GLClock_ShowTemp(unsigned char val, unsigned char sign)
{
	 GLClock_SetTemp(GL_FONT_SEGMENTAL28, val, sign);
}
