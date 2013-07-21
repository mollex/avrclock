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
extern  FontChar_t courierNew_8ptDescriptors[];
extern  unsigned char courierNew_8ptBitmaps[];

extern  FontChar_t courierNew_12ptDescriptors[];
extern  unsigned char courierNew_12ptBitmaps[];

extern  FontChar_t courierNew_14ptDescriptors[];
extern  unsigned char courierNew_14ptBitmaps[];

extern  FontChar_t arialNarrow_14ptDescriptors[];
extern  unsigned char arialNarrow_14ptBitmaps[];

int _Color = 1;
// Font information for Courier New 8pt
Font_t Font[] =
{
	{
		.heightPages = 1, //  Character height
		.pt = 7,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 1, //  Width, in pixels, of space character
		.charInfo = courierNew_8ptDescriptors, //  Character descriptor array
		.dataPtr = courierNew_8ptBitmaps, //  Character bitmap array
	},
	{
		.heightPages = 1, //  Character height
		.pt = 10,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 2, //  Width, in pixels, of space character
		.charInfo = courierNew_12ptDescriptors, //  Character descriptor array
		.dataPtr = courierNew_12ptBitmaps, //  Character bitmap array
	},
	{
		.heightPages = 1, //  Character height
		.pt = 12,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 2, //  Width, in pixels, of space character
		.charInfo = courierNew_14ptDescriptors, //  Character descriptor array
		.dataPtr = courierNew_14ptBitmaps, //  Character bitmap array
	},
	{
		.heightPages = 1, //  Character height
		.pt = 14,
		.startChar = '0', //  Start character
		.endChar = '9', //  End character
		.spacePixels = 2, //  Width, in pixels, of space character
		.charInfo = arialNarrow_14ptDescriptors, //  Character descriptor array
		.dataPtr = arialNarrow_14ptBitmaps, //  Character bitmap array
	},
};


VideoBuf_t	VideoBuf = {
	
	.xmax = VBUFF_X_MAX,
	.ymax = VBUFF_Y_MAX,
	.xline = VBUFF_X_LINE,
	.yline = VBUFF_Y_LINE,
	
};
/************************* Function Prototypes *****************************/
static void GL_Uart()
{
	int xl, yl;
	uint32_t b;
	
	printf("\f");
	for(yl=0; yl < VideoBuf.ymax; yl++){
		for(xl=0; xl < VideoBuf.xline; xl++){
			for(b=0; b < 16; b++){
				if(VideoBuf.vbuff[yl/16][xl][yl] & (1<<b)) printf("#");
				else printf(".");
			}
		}
		printf("\r\n");
	}
	
	memset(VideoBuf.vbuff, 0, sizeof(VideoBuf.vbuff));
}

void GL_SetPixel(uint16_t x, uint16_t y, uint8_t val)
{
	if(x > VideoBuf.xmax || y > VideoBuf.ymax)	return;
	
	uint16_t xline  = x/16;
	uint16_t yline = y/16;
	if(val)
	{
		VideoBuf.vbuff[yline][xline][y%16] |= (1 << (x%16));
	}
	else
	{
		VideoBuf.vbuff[yline][xline][y%16] &=  ~(1 << (x%16));
	}
}

int GL_DrawChar(Font_t *font, uint16_t x0, uint16_t y0, uint16_t ch, uint8_t colour)
{
	uint8_t i, j;

	if(ch < '0' || ch > '9') return 0;

	int index = ch - '0';
	for(j=0; j<font->pt; j+=font->heightPages)
	{
		for(i=0; i<font->charInfo[index].widthBits; i++)
		{
			GL_SetPixel(x0 + i, y0 + j,  font->dataPtr[j +  font->charInfo[index].offset] & (1<<i));
		}
	}

	return (i + font->spacePixels);
}

void GL_DrawNumber(Font_t *font, uint16_t x0, uint16_t y0, uint32_t num, uint8_t colour)
{
	uint8_t buffer[8] = {0};
	sprintf(buffer, "%05d", (int)(num & 0x1FFFF));

	uint8_t t, i=0;
	do{
		t = buffer[i++];
		//printf("off %d\n\r",x0);
		x0 += GL_DrawChar(font, x0, y0, t, colour);
	}
	while(t);
}
