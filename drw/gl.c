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
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/
extern  FontChar_t segmental_28ptDescriptors[];
extern  unsigned char segmental_28ptBitmaps[];

// Font information for Courier New 8pt
Font_t Font[] =
{
	{
		.heightPages = 2, //  Character height
		.pt = 52,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 2, //  Width, in pixels, of space character
		.charInfo = segmental_28ptDescriptors, //  Character descriptor array
		.dataPtr = segmental_28ptBitmaps, //  Character bitmap array
	},
};


VideoBuf_t	_VideoBuf = {

	.xmax = VBUFF_X_MAX,
	.ymax = VBUFF_Y_MAX,
	.xline = VBUFF_X_LINE,
	.yline = VBUFF_Y_LINE,

};
/************************* Function Prototypes *****************************/
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
void gl_setpixel(uint16_t x, uint16_t y, uint8_t val)
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
int GL_DrawChar(Font_t *font, uint16_t x0, uint16_t y0, uint16_t ch)
{
	uint8_t i, j;

	if(ch < '0' || ch > '9') return 0;

	int index = ch - '0';
	for(j=0; j<font->pt; j+=font->heightPages)
	{
		for(i=0; i<font->charInfo[index].widthBits; i++)
		{
			gl_setpixel(x0+i, y0,  font->dataPtr[font->charInfo[index].offset + j +  i/8] & (1<<(i%8)));
			//gl_setpixel(x0+i, y0,  pgm_read_word(&(font->dataPtr[font->charInfo[index].offset + j +  i/8])) & (1<<(i%8)));
		}
		y0++;
	}

	return (i + font->spacePixels);
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
void GL_DrawNumber(Font_t *font, uint16_t x0, uint16_t y0, uint32_t num, uint8_t colour)
{
	uint8_t buffer[8] = {0};
	sprintf(buffer, "%04d", (int)(num & 0x1FFFF));

	uint8_t t, i=0;
	do{
		t = buffer[i++];
		x0 += GL_DrawChar(font, x0, y0, t);
	}
	while(t);
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
void GLClock_SetHour(Font_t *font, char val)
{
	char hight = val/10 + '0';
	char low = val%10 + '0';

	GL_DrawChar(font, 0, 3, hight);
	GL_DrawChar(font, 16, 3, low);

}

void GLClock_SetMinutes(Font_t *font, char val)
{
	char hight = val/10 + '0';
	char low = val%10 + '0';

	GL_DrawChar(font, 34, 3, hight);
	GL_DrawChar(font, 50, 3, low);
}

void GLClock_SetDots(char val)
{
	gl_setpixel(31, 8,  val);
	gl_setpixel(31, 9,  val);
	gl_setpixel(31, 10,  val);
	gl_setpixel(32, 10,  val);
	gl_setpixel(32, 8,  val);
	gl_setpixel(32, 9,  val);
}
void GLClock_ShowClock(unsigned char hour, unsigned char min, unsigned char dot)
{
	GLClock_SetHour(&Font[0], hour);
	GLClock_SetMinutes(&Font[0], min);
	GLClock_SetDots(dot);
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
void GLClock_SetTemp(Font_t *font, unsigned char val, unsigned char sign)
{
	char hight = val/10 + '0';
	char low = val%10 + '0';

	GL_DrawChar(font, 12, 3, hight);
	GL_DrawChar(font, 20, 3, low);

	if(sign)
	{
		GL_DrawLine(2, 15, 6, 15, 1);
	}else
	{
		GL_DrawLine(4, 12, 4, 18, 1);
	}
}

void GLClock_ShowTemp(unsigned char val, unsigned char sign)
{
	 GLClock_SetTemp(&Font[0], val, sign);
}
