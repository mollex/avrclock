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
* @file gl.h
*
* Put short file description here  !
*
* 	Created on: 08.11.2012
*   	Author: mollex
*
******************************************************************************/

#ifndef GL_H_
#define GL_H_
/***************************** Include Files *******************************/
#include <stdint.h>
/************************** Constant Definitions ****************************/
#define GL_FONT_SEGMENTAL28	0

#define VBUFF_X_MAX		64
#define VBUFF_Y_MAX		32

#define VBUFF_X_LINE		VBUFF_X_MAX/8
#define VBUFF_Y_LINE		VBUFF_Y_MAX/16

/**************************** Type Definitions ******************************/
typedef struct
{
	uint16_t		xmax;
	uint16_t		ymax;
	uint16_t		xline;
	uint16_t		yline;
	uint8_t			vbuff[VBUFF_Y_LINE][VBUFF_X_LINE][16];

}VideoBuf_t;

VideoBuf_t	_VideoBuf;
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/

void GLClock_ShowClock(unsigned char hour, unsigned char min, unsigned char dot);
void GLClock_ShowTemp(unsigned char val, unsigned char sign);
void GLClock_SetDots(char val);

#endif /* GL_H_ */
