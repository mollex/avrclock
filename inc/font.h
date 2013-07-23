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
* @file font.h
*
* Put short file description here  !
*
* 	Created on: 08.11.2012
*   	Author: mollex
*
******************************************************************************/


#ifndef FONT_H_
#define FONT_H_

/***************************** Include Files *******************************/
#include <stdint.h>
#include <avr/pgmspace.h>
/************************** Constant Definitions ****************************/


/**************************** Type Definitions ******************************/



// This structure describes a single character's display information
typedef struct
{
	const char widthBits;					// width, in bits (or pixels), of the character
	const short offset;					// offset of the character's bitmap, in bytes, into the the FONT_INFO's data array
	
} FontChar_t;	

// Describes a single font
typedef struct
{
	char 			heightPages;	// height, in pages (8 pixels), of the font's characters
	char 			pt;				// height, in bytes font's characters
	char 			startChar;		// the first character in the font (e.g. in charInfo and data)
	char 			endChar;		// the last character in the font
	char			spacePixels;	// number of pixels that a space character takes up
	FontChar_t*		charInfo;		// pointer to array of char information
	unsigned char*	dataPtr;		// pointer to generated array of character visual representation
		
} Font_t;	
/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/



#endif /* FONT_H_ */
