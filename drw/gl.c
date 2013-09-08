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
#include <math.h>

#include "font.h"
#include "gl.h"
#include "rc5.h"
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/
extern void Eprom_MjrSave(unsigned char addr, char val);
extern char Eprom_MjrLoad(unsigned char addr);
/************************** Variable Definitions ****************************/
extern  FontChar_t segmental_28ptDescriptors[];
extern  unsigned char segmental_28ptBitmaps[];

extern  FontChar_t segoeCondensed_14ptDescriptors[];
extern  unsigned char segoeCondensed_14ptBitmaps[];

extern  FontChar_t consolas_20ptDescriptors[];
extern  unsigned char consolas_20ptBitmaps[];

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
		.pt = 28,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 1, //  Width, in pixels, of space character
		.charInfo = segoeCondensed_14ptDescriptors, //  Character descriptor array
		.dataPtr = segoeCondensed_14ptBitmaps, //  Character bitmap array
	},

	{
		.heightPages = 2, //  Character height
		.pt = 40,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 2, //  Width, in pixels, of space character
		.charInfo = consolas_20ptDescriptors, //  Character descriptor array
		.dataPtr = consolas_20ptBitmaps, //  Character bitmap array
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
void gl_setpixel(unsigned char x, unsigned char y, unsigned int val)
{
	if(x >= _VideoBuf.xmax || y >= _VideoBuf.ymax)	return;

	uint16_t xline  = x/8;
	uint16_t yline = y/16;
	if(val)
	{
		_VideoBuf.vbuff[_VideoBuf.vbnum][yline][xline][y%16] |= (1 << (x%8));
	}
	else
	{
		_VideoBuf.vbuff[_VideoBuf.vbnum][yline][xline][y%16] &=  ~(1 << (x%8));
	}
}
void gl_vbnumtgl()
{
	_VideoBuf.vbnum = _VideoBuf.vbnum ? 0 : 1;
	memset(&_VideoBuf.vbuff[_VideoBuf.vbnum], 0x00, sizeof(_VideoBuf.vbuff)/2);

}
void GL_ClearSector(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {

	unsigned char stepx, stepy;

	for(stepx = x0; stepx<x1; stepx++)
	{
		for(stepy = y0; stepy<y1; stepy++)
		{
			gl_setpixel(stepx,  stepy, color);
		}
	}
}
void GL_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {

	unsigned char dy = y1 - y0;
	unsigned char dx = x1 - x0;
	unsigned char stepx, stepy;

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
int GL_DrawChar(unsigned char font, unsigned char x0, unsigned char y0, char ch)
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
	for(j=0; j<fontPtr->pt/fontPtr->heightPages; j++)
	{
		gl_setpixel(x0+i, --y0, 0);
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
char GL_GetCharSize(unsigned char font, char ch)
{
	//tx_print_usart("\n\r Str  ");
	char b;

	if(ch == 0) return 0;

	if(ch >= 0xC0)
	{
		b = ch - 0x90 + 10;
	}else
	{
		b = ch;
	}

	int index = ch - '0';

	return _Font[font].charInfo[index].widthBits;
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
char GL_GetSpaceSize(unsigned char font)
{
	return _Font[font].spacePixels;
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
void GL_DrawStr(unsigned char font, unsigned char x0, unsigned char y0, char *str, unsigned char size, char sw)
{
	//tx_print_usart("\n\r Str  ");
	char b;
	do{
		if(*str == 0) break;

		if(*str >= 0xC0)
		{
		b = *str - 0x90 + 10;
		}else
		{
			b = *str;
		}
		x0 += GL_DrawChar(font, x0, y0, b);
		//tx_hexprint_usart(&b, 1);
		++str;

	}
	while(--size);

	if(sw)gl_vbnumtgl();
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
	char s[] = "ЗАГРУЗ";
	GL_DrawStr(GL_FONT_SEGOE14, 8, 8, s, sizeof(s), 1);
	GL_DrawDots4(60, 17, 1);
}
void GLClock_Phrase2(char mode)
{
	int i;
	char s[] = "ТЕХ";
	char s2[] = "ПЕРЕРЫВ";

	for(i = mode; i<64; i++)
	{
		_Font[GL_FONT_SEGOE14].spacePixels = 2;
		GL_DrawStr(GL_FONT_SEGOE14, 18, 2, s, sizeof(s), 0);
		GL_DrawDots4(47, 13, 1);

		GL_DrawStr(GL_FONT_SEGOE14, 0, 17, s2, sizeof(s2), 0);
		_Font[GL_FONT_SEGOE14].spacePixels = 1;

		GL_ClearSector(i, 0, 64, 32, 0);
		gl_vbnumtgl();
		//_delay_ms(5);
	}
}
void GLClock_Phrase3(char mode)
{
	int i;
	char s[] = "СЛИВ";
	char s2[] = "Т0ПЛИВА";

	for(i = mode; i<64; i++)
	{
		GL_DrawStr(GL_FONT_SEGOE14, 16, 2, s, sizeof(s), 0);
		GL_DrawStr(GL_FONT_SEGOE14, 0, 17, s2, sizeof(s2), 0);
		//GL_DrawDots4(58, 27, 1);

		GL_ClearSector(i, 0, 64, 32, 0);
		gl_vbnumtgl();
	}
}
void GLClock_Phrase4(char mode)
{
	int i;
	char s[] = "СПАСИБ0";

	for(i = mode; i<64; i++)
	{
		GL_DrawStr(GL_FONT_SEGOE14, 0, 9, s, sizeof(s), 0);

		GL_ClearSector(i, 0, 64, 32, 0);
		gl_vbnumtgl();
	}
}
void GLClock_Phrase5(char mode)
{
	int i;
	char s[] = "ЗИМНИЙ";
	char s2[] = "ДИЗЕЛЬ";

	_Font[GL_FONT_SEGOE14].spacePixels = 2;
	for(i = mode; i<64; i++)
	{
		GL_DrawStr(GL_FONT_SEGOE14, 0, 2, s, sizeof(s), 0);
		GL_DrawStr(GL_FONT_SEGOE14, 3, 17, s2, sizeof(s2), 0);

		GL_ClearSector(i, 0, 64, 32, 0);
		gl_vbnumtgl();
	}
	_Font[GL_FONT_SEGOE14].spacePixels = 1;
}
void GLClock_Phrase6(unsigned char font)
{
	char s[] = "12345";
	unsigned char size  = sizeof(s);
	int i, strsize, index, x = 64;
	char charsize, strlen;

	tx_print_usart("\n\r size  ");	tx_hexprint_usart(&(size), 1);

	strlen = strsize = 0;
	for(i=0; i<sizeof(s); i++)
	{
		strsize += GL_GetCharSize(font, s[i]) + GL_GetSpaceSize(font);
		tx_print_usart("\n\r strsize  ");	tx_hexprint_usart(&(strsize), 2);
		if((strsize > 78) && (strlen == 0))
		{
			strlen = i;
		}
	}
	strsize += 64;

	tx_print_usart("\n\r strsize  ");	tx_hexprint_usart(&(strsize), 2);
	tx_print_usart("\n\r strlen  ");	tx_hexprint_usart(&(strlen), 1);

	index = 0;
	charsize = GL_GetCharSize(font, s[index]) + GL_GetSpaceSize(font);

	for(i=0; i<strsize; i++)
	{
		if(x<0 && fabs(x) >= charsize)
		{
			x = 0;
			index++;
			charsize = GL_GetCharSize(font, s[index]) + GL_GetSpaceSize(font);
		}
		GL_DrawStr(font, x--, 0, &s[index], strlen, 1);
		_delay_ms(20);
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
void GLClock_SetSign(unsigned char sign)
{
			GL_DrawLine(4, 11, 4, 20, sign ? 0 : 1);
			GL_DrawLine(5, 11, 5, 20, sign ? 0 : 1);
	GL_DrawLine(0, 15, 9, 15, 1);
	GL_DrawLine(0, 16, 9, 16, 1);

}
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

	GLClock_SetSign(sign);
	gl_vbnumtgl();
}

void GLClock_ShowTemp(unsigned char val, unsigned char sign)
{
	 GLClock_SetTemp(GL_FONT_SEGMENTAL28, val, sign);
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
	gl_vbnumtgl();
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
	gl_vbnumtgl();
	return ret;
}

char GLClock_SetClockCorrect(unsigned char cmd)
{
	char ret = 1;
	static unsigned char val = 10;
	if(cmd == IR_COM_VSD_PtoP)
	{
		memset(_VideoBuf.vbuff, 0x0, sizeof(_VideoBuf.vbuff));
		val = Eprom_MjrLoad(0x10);
		if(val > 20)val = 10;

	}else if(cmd == IR_COM_OK)
	{
		Eprom_MjrSave(0x10,  val);
		ret = 0;
	}
	else
	{
		if(cmd == IR_COM_UP)
			{
				if(val<19)val++;
			}
		if(cmd == IR_COM_DOWN)
			{
				if(val > 1)val--;
			}
	}

	GLClock_SetSign((val/10)? 0 : 1);

	GL_DrawChar(GL_FONT_SEGMENTAL28, 11, 2, '0');
	GL_DrawChar(GL_FONT_SEGMENTAL28, 28, 2, '0' + ((val/10)? val % 10 : 10 - val));
	GL_DrawStr(GL_FONT_SEGOE14, 45, 17, "С", 1, 0);
	GL_DrawDots4(54, 28, 1);
	gl_vbnumtgl();
	return ret;
}
