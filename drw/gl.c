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
void ht1632c_sendBuffer8(uint8_t colour, uint8_t adress, uint8_t* src, size_t size);

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

/*
static void GL_Ht1632()
{
	int xl, yl, l, addr;
	uint8_t buff[16] = {0};
	uint8_t buff2[16] = {0};

	for(yl=0; yl < VideoBuf.yline; yl++){
		for(xl=0; xl < 2; xl++){

			addr = yl * 64 + xl * 16;

			for(l=0; l < 16; l++){

				uint16_t t =  VideoBuf.vbuff[yl][xl][l];
				 uint8_t b;
				 if(l<8){
					 for(b=0; b<8; b++)
					 {
						 buff[b] |= (t & (1<<b))?  (1<<l) : 0;
						 buff[b + 8] |= (t & (1<<(b+8)))?  (1<<l) : 0;
					 }
				 }else{
					 for(b=0; b<8; b++)
					 {
						 buff2[b] |= (t & (1<<b))?  (1<<(l&0x7)) : 0;
						 buff2[b + 8] |= (t & (1<<(b+8)))?  (1<<(l&0x7)) : 0;
					 }

				 }

			}
			ht1632c_sendBuffer8(_Color, addr, buff, sizeof(buff));
			ht1632c_sendBuffer8(_Color, addr+32, buff2, sizeof(buff2));
			memset(buff, 0, sizeof(buff));
			memset(buff2, 0, sizeof(buff2));

		}
	}
	//memset(VideoBuf.vbuff, 0, sizeof(VideoBuf.vbuff));
}
*/

void GL_Clear()
{
	//ht1632c_memset(3, 0x00, 0, 64);
}

void GL_Show()
{
	// GL_Uart();

	// GL_Ht1632();
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


void GL_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t colour) {

	uint16_t dy = y1 - y0;
	uint16_t dx = x1 - x0;
	uint16_t stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
	dy <<= 1;                                                  // dy is now 2*dy
	dx <<= 1;                                                  // dx is now 2*dx

	GL_SetPixel(x0, y0, colour);
	if (dx > dy) {
		int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                                // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;                                    // same as fraction -= 2*dy
			GL_SetPixel(x0, y0, colour);
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
			GL_SetPixel(x0, y0, colour);
		}
	}
}

/**
  * @brief  Displays a Rectangle.
  * @param  maxX - Maximum X coordinate
  * @param  minX - Minimum X coordinate
  * @param  maxY - Maximum Y coordinate
  * @param  minY - Minimum Y coordinate
  * @retval None
  */
void GL_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t xmax, uint16_t ymax, uint8_t colour)
{
	GL_DrawLine(x0,			y0,			x0 + xmax,  y0,			colour);
	GL_DrawLine(x0,			y0,			x0,			y0 + ymax,	colour);
	GL_DrawLine(x0,			y0+ ymax,	x0 + xmax,  y0 + ymax,	colour);
	GL_DrawLine(x0 + xmax,	y0,			x0+ xmax,	y0 + ymax,	colour);
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

	GL_Show();

}

void GL_Test()
{
		//GL_SetPixel(20, 2, 1);
		//GL_DrawRectangle(4, 1, 30, 10,  1);
		int color, i, val = 12345;

		//GL_DrawChar(&Font[0], 5, 0, '3', 1);
		//GL_DrawChar(&Font[0], 10, 0, '9', 1);

		for(color=1; color<4; color++)
				{
			_Color = color;
							for(i=0; i<50; i++)
								{
									GL_DrawNumber(&Font[0], 2, i/4,val++,color);
									_delay_ms(100);
								}

							for(i=0; i<30; i++)
							{
								val+=100;
								GL_DrawNumber(&Font[1], 0, 0,val,color);

								_delay_ms(300);
							}

							for(i=0; i<30; i++)
							{
								val+=100;
								GL_DrawNumber(&Font[3],0, 0,val,color);

								_delay_ms(300);
							}
							GL_Clear();
				}
		//GL_DrawNumber(&Font[0],2,0,1234,1);
		//_delay_ms(1500);

		//GL_Clear();
		//GL_DrawNumber(&Font[1],0,0,1234,1);
		//_delay_ms(1500);

		/*GL_Clear();
		GL_DrawNumber(&Font[3],1,0,1234,1);
		_delay_ms(1500);

		for(i=0; i<30; i++)
		{
			GL_DrawNumber(&Font[1], i,2,213,1);
			
			_delay_ms(50);
		}*/
		
		
		


}
