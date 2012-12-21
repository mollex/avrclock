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
* @file font_courierNew8pt.c
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
#include "font.h"
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/
//
//  Font data for Courier New 14pt
//

// Character bitmaps for Courier New 14pt
unsigned char courierNew_14ptBitmaps[] =
{
	// @0 '0' (8 pixels wide)
	0x3C, //   ####
	0x7E, //  ######
	0x66, //  ##  ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0x66, //  ##  ##
	0x7E, //  ######
	0x3C, //   ####

	// @12 '1' (8 pixels wide)
	0x18, //    ##
	0x1F, // #####
	0x1F, // #####
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0xFF, // ########
	0xFF, // ########

	// @24 '2' (8 pixels wide)
	0x3C, //   ####
	0x7E, //  ######
	0xE7, // ###  ###
	0xC3, // ##    ##
	0xC0, //       ##
	0x60, //      ##
	0x30, //     ##
	0x18, //    ##
	0x0C, //   ##
	0x06, //  ##
	0xFF, // ########
	0xFF, // ########

	// @36 '3' (9 pixels wide)
	0x78, 0x00, //    ####
	0xFE, 0x00, //  #######
	0x86, 0x01, //  ##    ##
	0x80, 0x01, //        ##
	0xC0, 0x01, //       ###
	0xF8, 0x00, //    #####
	0xF8, 0x00, //    #####
	0xC0, 0x01, //       ###
	0x80, 0x01, //        ##
	0x83, 0x01, // ##     ##
	0xFF, 0x00, // ########
	0x7E, 0x00, //  ######

	// @60 '4' (8 pixels wide)
	0x70, //     ###
	0x70, //     ###
	0x78, //    ####
	0x6C, //   ## ##
	0x6C, //   ## ##
	0x66, //  ##  ##
	0x63, // ##   ##
	0xFF, // ########
	0xFF, // ########
	0x60, //      ##
	0xF8, //    #####
	0xF8, //    #####

	// @72 '5' (8 pixels wide)
	0x7E, //  ######
	0x7E, //  ######
	0x06, //  ##
	0x06, //  ##
	0x3E, //  #####
	0x7E, //  ######
	0xE6, //  ##  ###
	0xC0, //       ##
	0xC0, //       ##
	0xE3, // ##   ###
	0x7F, // #######
	0x3E, //  #####

	// @84 '6' (8 pixels wide)
	0xF0, //     ####
	0xFC, //   ######
	0x0E, //  ###
	0x06, //  ##
	0x3B, // ## ###
	0x7F, // #######
	0xE7, // ###  ###
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xE6, //  ##  ###
	0x7E, //  ######
	0x3C, //   ####

	// @96 '7' (8 pixels wide)
	0xFF, // ########
	0xFF, // ########
	0xC3, // ##    ##
	0xE0, //      ###
	0x60, //      ##
	0x60, //      ##
	0x70, //     ###
	0x30, //     ##
	0x30, //     ##
	0x38, //    ###
	0x18, //    ##
	0x18, //    ##

	// @108 '8' (8 pixels wide)
	0x3C, //   ####
	0x7E, //  ######
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0x7E, //  ######
	0x7E, //  ######
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0x7E, //  ######
	0x3C, //   ####

	// @120 '9' (8 pixels wide)
	0x3C, //   ####
	0x7E, //  ######
	0x67, // ###  ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xE7, // ###  ###
	0xFE, //  #######
	0xDC, //   ### ##
	0x60, //      ##
	0x70, //     ###
	0x3F, // ######
	0x0F, // ####
};

// Character descriptors for Courier New 14pt
// { [Char width in bits], [Offset into courierNew_14ptCharBitmaps in bytes] }
FontChar_t courierNew_14ptDescriptors[] =
{
	{8, 0}, 		// 0
	{8, 12}, 		// 1
	{8, 24}, 		// 2
	{9, 36}, 		// 3
	{8, 60}, 		// 4
	{8, 72}, 		// 5
	{8, 84}, 		// 6
	{8, 96}, 		// 7
	{8, 108}, 		// 8
	{8, 120}, 		// 9
};
/*
// Font information for Courier New 14pt
const FONT_INFO courierNew_14ptFontInfo =
{
	2, //  Character height
	'0', //  Start character
	'9', //  End character
	courierNew_14ptDescriptors, //  Character descriptor array
	courierNew_14ptBitmaps, //  Character bitmap array
};

*/
