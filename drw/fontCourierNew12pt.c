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
//  Font data for Courier New 12pt
//

// Character bitmaps for Courier New 12pt
unsigned char courierNew_12ptBitmaps[] =
{
	// @0 '0' (6 pixels wide)
	0x1E, //  ####
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x1E, //  ####

	// @10 '1' (7 pixels wide)
	0x0C, //   ##
	0x0B, // ## #
	0x08, //    #
	0x08, //    #
	0x08, //    #
	0x08, //    #
	0x08, //    #
	0x08, //    #
	0x08, //    #
	0x7F, // #######

	// @20 '2' (7 pixels wide)
	0x3E, //  #####
	0x41, // #     #
	0x41, // #     #
	0x40, //       #
	0x20, //      #
	0x18, //    ##
	0x04, //   #
	0x02, //  #
	0x41, // #     #
	0x7F, // #######

	// @30 '3' (7 pixels wide)
	0x3C, //   ####
	0x43, // ##    #
	0x40, //       #
	0x40, //       #
	0x38, //    ###
	0x20, //      #
	0x40, //       #
	0x40, //       #
	0x41, // #     #
	0x3E, //  #####

	// @40 '4' (6 pixels wide)
	0x10, //     #
	0x18, //    ##
	0x14, //   # #
	0x12, //  #  #
	0x12, //  #  #
	0x11, // #   #
	0x3F, // ######
	0x10, //     #
	0x10, //     #
	0x3C, //   ####

	// @50 '5' (7 pixels wide)
	0x3E, //  #####
	0x02, //  #
	0x02, //  #
	0x02, //  #
	0x3E, //  #####
	0x40, //       #
	0x40, //       #
	0x40, //       #
	0x41, // #     #
	0x3E, //  #####

	// @60 '6' (7 pixels wide)
	0x78, //    ####
	0x04, //   #
	0x02, //  #
	0x01, // #
	0x3D, // # ####
	0x43, // ##    #
	0x41, // #     #
	0x41, // #     #
	0x41, // #     #
	0x3E, //  #####

	// @70 '7' (7 pixels wide)
	0x7F, // #######
	0x41, // #     #
	0x40, //       #
	0x20, //      #
	0x20, //      #
	0x10, //     #
	0x10, //     #
	0x10, //     #
	0x08, //    #
	0x08, //    #

	// @80 '8' (6 pixels wide)
	0x1E, //  ####
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x1E, //  ####
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x1E, //  ####

	// @90 '9' (6 pixels wide)
	0x1E, //  ####
	0x21, // #    #
	0x21, // #    #
	0x21, // #    #
	0x31, // #   ##
	0x2E, //  ### #
	0x20, //      #
	0x10, //     #
	0x08, //    #
	0x07, // ###
};

// Character descriptors for Courier New 12pt
// { [Char width in bits], [Offset into courierNew_12ptCharBitmaps in bytes] }
FontChar_t courierNew_12ptDescriptors[] =
{
	{6, 0}, 		// 0
	{7, 10}, 		// 1
	{7, 20}, 		// 2
	{7, 30}, 		// 3
	{6, 40}, 		// 4
	{7, 50}, 		// 5
	{7, 60}, 		// 6
	{7, 70}, 		// 7
	{6, 80}, 		// 8
	{6, 90}, 		// 9
};

