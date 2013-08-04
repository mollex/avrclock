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

// Character bitmaps for Courier New 8pt
unsigned char courierNew_8ptBitmaps[]   =
{
	// @0 '0' (5 pixels wide)
	0x0E, //  ### 
	0x11, // #   #
	0x11, // #   #
	0x11, // #   #
	0x11, // #   #
	0x11, // #   #
	0x0E, //  ### 

	// @7 '1' (5 pixels wide)
	0x06, //  ##  
	0x04, //   #  
	0x04, //   #  
	0x04, //   #  
	0x04, //   #  
	0x04, //   #  
	0x1F, // #####

	// @14 '2' (5 pixels wide)
	0x0E, //  ### 
	0x11, // #   #
	0x08, //    # 
	0x04, //   #  
	0x02, //  #   
	0x01, // #    
	0x1F, // #####

	// @21 '3' (5 pixels wide)
	0x0E, //  ### 
	0x11, // #   #
	0x10, //     #
	0x0C, //   ## 
	0x10, //     #
	0x11, // #   #
	0x0E, //  ### 

	// @28 '4' (5 pixels wide)
	0x08, //    # 
	0x0C, //   ## 
	0x0A, //  # # 
	0x09, // #  # 
	0x1F, // #####
	0x08, //    # 
	0x1C, //   ###

	// @35 '5' (5 pixels wide)
	0x1E, //  ####
	0x02, //  #   
	0x02, //  #   
	0x0E, //  ### 
	0x10, //     #
	0x11, // #   #
	0x0E, //  ### 

	// @42 '6' (5 pixels wide)
	0x1C, //   ###
	0x02, //  #   
	0x01, // #    
	0x0F, // #### 
	0x11, // #   #
	0x11, // #   #
	0x0E, //  ### 

	// @49 '7' (5 pixels wide)
	0x1F, // #####
	0x11, // #   #
	0x10, //     #
	0x08, //    # 
	0x08, //    # 
	0x04, //   #  
	0x04, //   #  

	// @56 '8' (5 pixels wide)
	0x0E, //  ### 
	0x11, // #   #
	0x11, // #   #
	0x0E, //  ### 
	0x11, // #   #
	0x11, // #   #
	0x0E, //  ### 

	// @63 '9' (5 pixels wide)
	0x0E, //  ### 
	0x11, // #   #
	0x11, // #   #
	0x1E, //  ####
	0x10, //     #
	0x08, //    # 
	0x07, // ###  
};

// Character descriptors for Courier New 8pt
// { [Char width in bits], [Offset into courierNew_8ptCharBitmaps in bytes] }
FontChar_t courierNew_8ptDescriptors[] = 
{
	{5, 0}, 		// 0 
	{5, 7}, 		// 1 
	{5, 14}, 		// 2 
	{5, 21}, 		// 3 
	{5, 28}, 		// 4 
	{5, 35}, 		// 5 
	{5, 42}, 		// 6 
	{5, 49}, 		// 7 
	{5, 56}, 		// 8 
	{5, 63}, 		// 9 
};
