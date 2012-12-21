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
//  Font data for Arial Narrow 14pt
//

// Character bitmaps for Arial Narrow 14pt
unsigned char arialNarrow_14ptBitmaps[] =
{
	// @0 '0' (7 pixels wide)
	0x1C, //   ###
	0x3E, //  #####
	0x36, //  ## ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x36, //  ## ##
	0x3E, //  #####
	0x1C, //   ###

	// @14 '1' (5 pixels wide)
	0x18, //    ##
	0x18, //    ##
	0x1C, //   ###
	0x1E, //  ####
	0x1B, // ## ##
	0x19, // #  ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##

	// @28 '2' (8 pixels wide)
	0x3C, //   ####
	0x7E, //  ######
	0xC7, // ###   ##
	0xC3, // ##    ##
	0xC0, //       ##
	0xC0, //       ##
	0x60, //      ##
	0x70, //     ###
	0x38, //    ###
	0x1C, //   ###
	0x0E, //  ###
	0x0E, //  ###
	0xFF, // ########
	0xFF, // ########

	// @42 '3' (7 pixels wide)
	0x1C, //   ###
	0x3E, //  #####
	0x67, // ###  ##
	0x63, // ##   ##
	0x60, //      ##
	0x38, //    ###
	0x38, //    ###
	0x60, //      ##
	0x60, //      ##
	0x60, //      ##
	0x63, // ##   ##
	0x77, // ### ###
	0x3E, //  #####
	0x1C, //   ###

	// @56 '4' (8 pixels wide)
	0x60, //      ##
	0x70, //     ###
	0x70, //     ###
	0x78, //    ####
	0x78, //    ####
	0x6C, //   ## ##
	0x6E, //  ### ##
	0x66, //  ##  ##
	0x63, // ##   ##
	0xFF, // ########
	0xFF, // ########
	0x60, //      ##
	0x60, //      ##
	0x60, //      ##

	// @70 '5' (7 pixels wide)
	0x3E, //  #####
	0x3E, //  #####
	0x06, //  ##
	0x07, // ###
	0x1B, // ## ##
	0x3F, // ######
	0x73, // ##  ###
	0x60, //      ##
	0x60, //      ##
	0x60, //      ##
	0x63, // ##   ##
	0x77, // ### ###
	0x3E, //  #####
	0x1C, //   ###

	// @84 '6' (7 pixels wide)
	0x1C, //   ###
	0x3E, //  #####
	0x66, //  ##  ##
	0x63, // ##   ##
	0x03, // ##
	0x1F, // #####
	0x3F, // ######
	0x73, // ##  ###
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x66, //  ##  ##
	0x3E, //  #####
	0x1C, //   ###

	// @98 '7' (7 pixels wide)
	0x7F, // #######
	0x7F, // #######
	0x60, //      ##
	0x30, //     ##
	0x30, //     ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x18, //    ##
	0x0C, //   ##
	0x0C, //   ##
	0x0C, //   ##
	0x0C, //   ##
	0x0C, //   ##

	// @112 '8' (7 pixels wide)
	0x3E, //  #####
	0x7F, // #######
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x3E, //  #####
	0x3E, //  #####
	0x77, // ### ###
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x77, // ### ###
	0x3E, //  #####
	0x1C, //   ###

	// @126 '9' (7 pixels wide)
	0x1C, //   ###
	0x3E, //  #####
	0x33, // ##  ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x63, // ##   ##
	0x77, // ### ###
	0x7E, //  ######
	0x7C, //   #####
	0x60, //      ##
	0x63, // ##   ##
	0x33, // ##  ##
	0x3E, //  #####
	0x1C, //   ###
};

// Character descriptors for Arial Narrow 14pt
// { [Char width in bits], [Offset into arialNarrow_14ptCharBitmaps in bytes] }
FontChar_t  arialNarrow_14ptDescriptors[] =
{
	{7, 0}, 		// 0
	{5, 14}, 		// 1
	{8, 28}, 		// 2
	{7, 42}, 		// 3
	{8, 56}, 		// 4
	{7, 70}, 		// 5
	{7, 84}, 		// 6
	{7, 98}, 		// 7
	{7, 112}, 		// 8
	{7, 126}, 		// 9
};
