/******************************************************************************
*
* (c) Copyright 2013 Peleng, Inc. All rights reserved.
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
* @file    console_20ptBitmaps.c
* @author  mollex
* @version v1.00a
* @date    04.09.2013
* @brief   Put short file description here  !
* 
* MODIFICATION HISTORY:
*
* Ver   Who      Date        Changes
* ----- -------- ----------  -----------------------------------------------
* 1.00a mollex	 04.09.2013	First release
*
******************************************************************************/

/****************************** Include Files *******************************/
#include "font.h"
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/

// Character bitmaps for Consolas 20pt
unsigned char consolas_20ptBitmaps[] PROGMEM =
{
	// @0 '0' (13 pixels wide)
/*	0xF0, 0x01, //     #####
	0xFC, 0x07, //   #########
	0x1C, 0x0F, //   ###   ####
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x0E, //  ###     ###
	0x07, 0x1E, // ###      ####
	0x07, 0x1F, // ###     #####
	0xC7, 0x1D, // ###   ### ###
	0xE7, 0x1C, // ###  ###  ###
	0x77, 0x1C, // ### ###   ###
	0x1F, 0x1C, // #####     ###
	0x0F, 0x1C, // ####      ###
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x0E, //  ###     ###
	0x1E, 0x07, //  ####   ###
	0xFC, 0x07, //   #########
	0xF0, 0x01, //     #####

	// @34 '1' (11 pixels wide)
	0xE0, 0x00, //      ###
	0xF8, 0x00, //    #####
	0xEE, 0x00, //  ### ###
	0xE7, 0x00, // ###  ###
	0xE2, 0x00, //  #   ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xFE, 0x07, //  ##########
	0xFE, 0x07, //  ##########

	// @68 '2' (11 pixels wide)
	0x7C, 0x00, //   #####
	0xFE, 0x01, //  ########
	0xC7, 0x01, // ###   ###
	0x82, 0x03, //  #     ###
	0x80, 0x03, //        ###
	0x80, 0x03, //        ###
	0x80, 0x03, //        ###
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###
	0xE0, 0x00, //      ###
	0x70, 0x00, //     ###
	0x38, 0x00, //    ###
	0x1C, 0x00, //   ###
	0x0E, 0x00, //  ###
	0x06, 0x00, //  ##
	0xFF, 0x07, // ###########
	0xFF, 0x07, // ###########

	// @102 '3' (11 pixels wide)
	0x7E, 0x00, //  ######
	0xFF, 0x01, // #########
	0xC1, 0x03, // #     ####
	0x80, 0x03, //        ###
	0x80, 0x03, //        ###
	0x80, 0x03, //        ###
	0xC0, 0x01, //       ###
	0xFC, 0x00, //   ######
	0xFC, 0x01, //   #######
	0xC0, 0x03, //       ####
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0xC0, 0x03, //       ####
	0xFF, 0x01, // #########
	0x7F, 0x00, // #######

	// @136 '4' (14 pixels wide)
	0x00, 0x0F, //         ####
	0x80, 0x0F, //        #####
	0xC0, 0x0F, //       ######
	0xE0, 0x0E, //      ### ###
	0x60, 0x0E, //      ##  ###
	0x30, 0x0E, //     ##   ###
	0x38, 0x0E, //    ###   ###
	0x18, 0x0E, //    ##    ###
	0x0C, 0x0E, //   ##     ###
	0x06, 0x0E, //  ##      ###
	0x07, 0x0E, // ###      ###
	0xFF, 0x3F, // ##############
	0xFF, 0x3F, // ##############
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###

	// @170 '5' (11 pixels wide)
	0xFF, 0x03, // ##########
	0xFF, 0x03, // ##########
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0xFF, 0x00, // ########
	0xFF, 0x03, // ##########
	0xC0, 0x07, //       #####
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0x80, 0x07, //        ####
	0xC0, 0x03, //       ####
	0xFF, 0x01, // #########
	0x7F, 0x00, // #######

	// @204 '6' (12 pixels wide)
	0xE0, 0x07, //      ######
	0xF8, 0x07, //    ########
	0x3C, 0x00, //   ####
	0x1E, 0x00, //  ####
	0x0E, 0x00, //  ###
	0x06, 0x00, //  ##
	0x07, 0x00, // ###
	0xF7, 0x03, // ### ######
	0xFF, 0x07, // ###########
	0x0F, 0x0F, // ####    ####
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x07, //  ###    ###
	0xFC, 0x03, //   ########
	0xF8, 0x01, //    ######

	// @238 '7' (12 pixels wide)
	0xFF, 0x0F, // ############
	0xFF, 0x0F, // ############
	0x00, 0x0E, //          ###
	0x00, 0x06, //          ##
	0x00, 0x07, //         ###
	0x00, 0x03, //         ##
	0x80, 0x03, //        ###
	0x80, 0x01, //        ##
	0xC0, 0x01, //       ###
	0xC0, 0x00, //       ##
	0xE0, 0x00, //      ###
	0x60, 0x00, //      ##
	0x70, 0x00, //     ###
	0x30, 0x00, //     ##
	0x38, 0x00, //    ###
	0x18, 0x00, //    ##
	0x1C, 0x00, //   ###

	// @272 '8' (12 pixels wide)
	0xF8, 0x01, //    ######
	0xFE, 0x07, //  ##########
	0x0F, 0x0F, // ####    ####
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x0F, 0x0E, // ####     ###
	0x9E, 0x07, //  ####  ####
	0xFC, 0x01, //   #######
	0xF8, 0x03, //    #######
	0x9E, 0x07, //  ####  ####
	0x0E, 0x0F, //  ###    ####
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x0F, 0x0F, // ####    ####
	0xFE, 0x07, //  ##########
	0xF8, 0x01, //    ######

	// @306 '9' (13 pixels wide)
	0xF0, 0x01, //     #####
	0xFC, 0x07, //   #########
	0x1E, 0x0F, //  ####   ####
	0x0F, 0x0E, // ####     ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x0E, 0x1E, //  ###     ####
	0xFE, 0x1F, //  ############
	0xF8, 0x1D, //    ###### ###
	0x00, 0x0C, //           ##
	0x00, 0x0E, //          ###
	0x00, 0x07, //         ###
	0x80, 0x07, //        ####
	0xFE, 0x01, //  ########
	0x7E, 0x00, //  ######

	// @340 ':' (4 pixels wide)
	0x06, //  ##
	0x0F, // ####
	0x0F, // ####
	0x06, //  ##
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x06, //  ##
	0x0F, // ####
	0x0F, // ####
	0x06, //  ##

	// @353 ';' (6 pixels wide)
	0x18, //    ##
	0x3C, //   ####
	0x3C, //   ####
	0x18, //    ##
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x1C, //   ###
	0x3C, //   ####
	0x3C, //   ####
	0x38, //    ###
	0x38, //    ###
	0x38, //    ###
	0x1C, //   ###
	0x0F, // ####
	0x07, // ###

	// @371 '<' (10 pixels wide)
	0x00, 0x01, //         #
	0x80, 0x03, //        ###
	0xC0, 0x01, //       ###
	0xE0, 0x00, //      ###
	0x38, 0x00, //    ###
	0x1C, 0x00, //   ###
	0x0E, 0x00, //  ###
	0x07, 0x00, // ###
	0x0E, 0x00, //  ###
	0x1C, 0x00, //   ###
	0x78, 0x00, //    ####
	0xE0, 0x00, //      ###
	0xC0, 0x01, //       ###
	0x80, 0x03, //        ###
	0x00, 0x01, //         #

	// @401 '=' (11 pixels wide)
	0xFF, 0x07, // ###########
	0xFF, 0x07, // ###########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0xFF, 0x07, // ###########
	0xFF, 0x07, // ###########

	// @415 '>' (10 pixels wide)
	0x02, 0x00, //  #
	0x07, 0x00, // ###
	0x0E, 0x00, //  ###
	0x1C, 0x00, //   ###
	0x78, 0x00, //    ####
	0xE0, 0x00, //      ###
	0xC0, 0x01, //       ###
	0x80, 0x03, //        ###
	0xC0, 0x01, //       ###
	0xE0, 0x00, //      ###
	0x70, 0x00, //     ###
	0x1C, 0x00, //   ###
	0x0E, 0x00, //  ###
	0x07, 0x00, // ###
	0x02, 0x00, //  #

	// @445 '?' (9 pixels wide)
	0x0F, 0x00, // ####
	0x3F, 0x00, // ######
	0x78, 0x00, //    ####
	0xE0, 0x00, //      ###
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###
	0xE0, 0x01, //      ####
	0xFC, 0x00, //   ######
	0x7C, 0x00, //   #####
	0x1C, 0x00, //   ###
	0x1C, 0x00, //   ###
	0x1C, 0x00, //   ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x0E, 0x00, //  ###
	0x0E, 0x00, //  ###
	0x0E, 0x00, //  ###

	// @483 '_' (15 pixels wide)
	0xFF, 0x7F, // ###############
	0xFF, 0x7F, // ###############

	// @487 '�' (13 pixels wide)
	0xE0, 0x00, //      ###
	0xA0, 0x01, //      # ##
	0xB0, 0x01, //     ## ##
	0xB0, 0x01, //     ## ##
	0xB0, 0x03, //     ## ###
	0x18, 0x03, //    ##   ##
	0x18, 0x03, //    ##   ##
	0x18, 0x07, //    ##   ###
	0x0C, 0x06, //   ##     ##
	0x0C, 0x06, //   ##     ##
	0x0C, 0x06, //   ##     ##
	0xFE, 0x0F, //  ###########
	0xFE, 0x0F, //  ###########
	0x06, 0x0C, //  ##       ##
	0x07, 0x1C, // ###       ###
	0x03, 0x18, // ##         ##
	0x03, 0x18, // ##         ##

	// @521 '�' (12 pixels wide)
	0xFF, 0x07, // ###########
	0xFF, 0x07, // ###########
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0xFF, 0x01, // #########
	0xFF, 0x07, // ###########
	0x07, 0x07, // ###     ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x07, // ###     ###
	0xFF, 0x03, // ##########
	0xFF, 0x00, // ########

	// @555 '�' (12 pixels wide)
	0xFF, 0x01, // #########
	0xFF, 0x03, // ##########
	0x87, 0x07, // ###    ####
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x87, 0x03, // ###    ###
	0xFF, 0x01, // #########
	0xFF, 0x03, // ##########
	0x07, 0x07, // ###     ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x07, // ###     ###
	0xFF, 0x03, // ##########
	0xFF, 0x00, // ########

	// @589 '�' (10 pixels wide)
	0xFF, 0x03, // ##########
	0xFF, 0x03, // ##########
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###

	// @623 '�' (15 pixels wide)
	0xF0, 0x1F, //     #########
	0xF0, 0x1F, //     #########
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x78, 0x1C, //    ####   ###
	0x78, 0x1C, //    ####   ###
	0x38, 0x1C, //    ###    ###
	0x38, 0x1C, //    ###    ###
	0x38, 0x1C, //    ###    ###
	0x3C, 0x1C, //   ####    ###
	0x1E, 0x1C, //  ####     ###
	0xFF, 0x7F, // ###############
	0xFF, 0x7F, // ###############
	0x07, 0x70, // ###         ###
	0x07, 0x70, // ###         ###
	0x07, 0x70, // ###         ###
	0x07, 0x70, // ###         ###

	// @665 '�' (10 pixels wide)
	0xFF, 0x03, // ##########
	0xFF, 0x03, // ##########
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0xFF, 0x03, // ##########
	0xFF, 0x03, // ##########
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0xFF, 0x03, // ##########
	0xFF, 0x03, // ##########

	// @699 '�' (16 pixels wide)
	0xC7, 0xE1, // ###   ###    ###
	0xCE, 0x71, //  ###  ###   ###
	0xCE, 0x71, //  ###  ###   ###
	0xCE, 0x39, //  ###  ###  ###
	0xDC, 0x39, //   ### ###  ###
	0xDC, 0x1D, //   ### ### ###
	0xDC, 0x1D, //   ### ### ###
	0xF8, 0x0F, //    #########
	0xF8, 0x0F, //    #########
	0xF8, 0x1D, //    ###### ###
	0xDC, 0x1D, //   ### ### ###
	0xDC, 0x3D, //   ### ### ####
	0xDC, 0x39, //   ### ###  ###
	0xCE, 0x39, //  ###  ###  ###
	0xCE, 0x71, //  ###  ###   ###
	0xCE, 0x71, //  ###  ###   ###
	0xC7, 0xE1, // ###   ###    ###

	// @733 '�' (12 pixels wide)
	0xFE, 0x00, //  #######
	0xFF, 0x03, // ##########
	0x81, 0x07, // #      ####
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0x00, 0x07, //         ###
	0x80, 0x03, //        ###
	0xFE, 0x01, //  ########
	0xFE, 0x03, //  #########
	0x80, 0x07, //        ####
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x81, 0x07, // #      ####
	0xFF, 0x03, // ##########
	0xFE, 0x00, //  #######

	// @767 '�' (12 pixels wide)
	0x07, 0x0E, // ###      ###
	0x07, 0x0F, // ###     ####
	0x07, 0x0F, // ###     ####
	0x87, 0x0F, // ###    #####
	0x87, 0x0F, // ###    #####
	0x87, 0x0E, // ###    # ###
	0xC7, 0x0E, // ###   ## ###
	0x47, 0x0E, // ###   #  ###
	0x67, 0x0E, // ###  ##  ###
	0x27, 0x0E, // ###  #   ###
	0x37, 0x0E, // ### ##   ###
	0x37, 0x0E, // ### ##   ###
	0x1F, 0x0E, // #####    ###
	0x1F, 0x0E, // #####    ###
	0x0F, 0x0E, // ####     ###
	0x0F, 0x0E, // ####     ###
	0x07, 0x0E, // ###      ###

	// @801 '�' (12 pixels wide)
	0x87, 0x03, // ###    ###
	0x87, 0x03, // ###    ###
	0xFE, 0x01, //  ########
	0xFC, 0x00, //   ######
	0x00, 0x00, //
	0x07, 0x0E, // ###      ###
	0x07, 0x0F, // ###     ####
	0x07, 0x0F, // ###     ####
	0x87, 0x0F, // ###    #####
	0x87, 0x0F, // ###    #####
	0x87, 0x0E, // ###    # ###
	0xC7, 0x0E, // ###   ## ###
	0x47, 0x0E, // ###   #  ###
	0x67, 0x0E, // ###  ##  ###
	0x27, 0x0E, // ###  #   ###
	0x37, 0x0E, // ### ##   ###
	0x37, 0x0E, // ### ##   ###
	0x1F, 0x0E, // #####    ###
	0x1F, 0x0E, // #####    ###
	0x0F, 0x0E, // ####     ###
	0x0F, 0x0E, // ####     ###
	0x07, 0x0E, // ###      ###

	// @845 '�' (12 pixels wide)
	0x07, 0x06, // ###      ##
	0x07, 0x07, // ###     ###
	0x87, 0x03, // ###    ###
	0xC7, 0x01, // ###   ###
	0xC7, 0x00, // ###   ##
	0x67, 0x00, // ###  ##
	0x77, 0x00, // ### ###
	0x37, 0x00, // ### ##
	0x1F, 0x00, // #####
	0x37, 0x00, // ### ##
	0x77, 0x00, // ### ###
	0xE7, 0x00, // ###  ###
	0xC7, 0x00, // ###   ##
	0xC7, 0x01, // ###   ###
	0x87, 0x03, // ###    ###
	0x07, 0x07, // ###     ###
	0x07, 0x0E, // ###      ###

	// @879 '�' (13 pixels wide)
	0xF0, 0x1F, //     #########
	0xF0, 0x1F, //     #########
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x70, 0x1C, //     ###   ###
	0x78, 0x1C, //    ####   ###
	0x38, 0x1C, //    ###    ###
	0x38, 0x1C, //    ###    ###
	0x38, 0x1C, //    ###    ###
	0x38, 0x1C, //    ###    ###
	0x38, 0x1C, //    ###    ###
	0x1C, 0x1C, //   ###     ###
	0x1E, 0x1C, //  ####     ###
	0x0F, 0x1C, // ####      ###
	0x07, 0x1C, // ###       ###

	// @913 '�' (14 pixels wide)
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x1E, //  ###     ####
	0x0E, 0x1A, //  ###     # ##
	0x1E, 0x1B, //  ####   ## ##
	0x1E, 0x1B, //  ####   ## ##
	0x16, 0x19, //  ## #   #  ##
	0xB6, 0x19, //  ## ## ##  ##
	0xB6, 0x18, //  ## ## #   ##
	0xA6, 0x18, //  ##  # #   ##
	0xE7, 0x18, // ###  ###   ##
	0x67, 0x18, // ###  ##    ##
	0x07, 0x18, // ###        ##
	0x07, 0x18, // ###        ##
	0x07, 0x38, // ###        ###
	0x07, 0x38, // ###        ###
	0x07, 0x38, // ###        ###
	0x07, 0x38, // ###        ###

	// @947 '�' (12 pixels wide)
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0xFF, 0x0F, // ############
	0xFF, 0x0F, // ############
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###

	// @981 '�' (13 pixels wide)
	0xF0, 0x01, //     #####
	0xF8, 0x07, //    ########
	0x1C, 0x0F, //   ###   ####
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x1E, //  ###     ####
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x0F, 0x0E, // ####     ###
	0x0E, 0x0E, //  ###     ###
	0x1E, 0x07, //  ####   ###
	0xFC, 0x03, //   ########
	0xF0, 0x01, //     #####

	// @1015 '�' (12 pixels wide)
	0xFF, 0x0F, // ############
	0xFF, 0x0F, // ############
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###

	// @1049 '�' (12 pixels wide)
	0xFF, 0x01, // #########
	0xFF, 0x03, // ##########
	0x87, 0x07, // ###    ####
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0F, // ###     ####
	0x87, 0x07, // ###    ####
	0xFF, 0x03, // ##########
	0xFF, 0x00, // ########
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###

	// @1083 '�' (12 pixels wide)
	0xE0, 0x07, //      ######
	0xF8, 0x0F, //    #########
	0x3C, 0x08, //   ####     #
	0x1E, 0x00, //  ####
	0x0E, 0x00, //  ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x0E, 0x00, //  ###
	0x0E, 0x00, //  ###
	0x3C, 0x08, //   ####     #
	0xF8, 0x0F, //    #########
	0xF0, 0x07, //     #######

	// @1117 '�' (13 pixels wide)
	0xFF, 0x1F, // #############
	0xFF, 0x1F, // #############
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###

	// @1151 '�' (12 pixels wide)
	0x03, 0x0C, // ##        ##
	0x07, 0x0E, // ###      ###
	0x06, 0x06, //  ##      ##
	0x0E, 0x06, //  ###     ##
	0x0C, 0x07, //   ##    ###
	0x1C, 0x03, //   ###   ##
	0x98, 0x03, //    ##  ###
	0xB8, 0x01, //    ### ##
	0xB0, 0x01, //     ## ##
	0xF0, 0x01, //     #####
	0xE0, 0x00, //      ###
	0xE0, 0x00, //      ###
	0x60, 0x00, //      ##
	0x60, 0x00, //      ##
	0x70, 0x00, //     ###
	0x3E, 0x00, //  #####
	0x1E, 0x00, //  ####

	// @1185 '�' (15 pixels wide)
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###
	0xF0, 0x07, //     #######
	0xFC, 0x1F, //   ###########
	0xDE, 0x3D, //  #### ### ####
	0xCE, 0x79, //  ###  ###  ####
	0xC7, 0x71, // ###   ###   ###
	0xC7, 0x71, // ###   ###   ###
	0xC7, 0x71, // ###   ###   ###
	0xC7, 0x71, // ###   ###   ###
	0xC7, 0x71, // ###   ###   ###
	0xCF, 0x39, // ####  ###  ###
	0xCE, 0x3D, //  ###  ### ####
	0xFC, 0x1F, //   ###########
	0xF8, 0x07, //    ########
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###

	// @1219 '�' (15 pixels wide)
	0x0E, 0x38, //  ###       ###
	0x1C, 0x1C, //   ###     ###
	0x18, 0x0C, //    ##     ##
	0x38, 0x0E, //    ###   ###
	0x70, 0x07, //     ### ###
	0xE0, 0x03, //      #####
	0xE0, 0x03, //      #####
	0xC0, 0x01, //       ###
	0xC0, 0x01, //       ###
	0xE0, 0x03, //      #####
	0x70, 0x07, //     ### ###
	0x70, 0x07, //     ### ###
	0x38, 0x0E, //    ###   ###
	0x1C, 0x1C, //   ###     ###
	0x1C, 0x1C, //   ###     ###
	0x0E, 0x38, //  ###       ###
	0x07, 0x70, // ###         ###

	// @1253 '�' (13 pixels wide)
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0x07, 0x07, // ###     ###
	0xFF, 0x1F, // #############
	0xFF, 0x1F, // #############
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###

	// @1295 '�' (13 pixels wide)
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x0E, 0x1C, //  ###      ###
	0xFE, 0x1F, //  ############
	0xF8, 0x1F, //    ##########
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###

	// @1329 '�' (13 pixels wide)
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xFF, 0x1F, // #############
	0xFF, 0x1F, // #############

	// @1363 '�' (14 pixels wide)
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xE7, 0x1C, // ###  ###  ###
	0xFF, 0x3F, // ##############
	0xFF, 0x3F, // ##############
	0x00, 0x38, //            ###
	0x00, 0x38, //            ###
	0x00, 0x38, //            ###
	0x00, 0x38, //            ###

	// @1405 '�' (14 pixels wide)
	0x3F, 0x00, // ######
	0x3F, 0x00, // ######
	0x38, 0x00, //    ###
	0x38, 0x00, //    ###
	0x38, 0x00, //    ###
	0x38, 0x00, //    ###
	0x38, 0x00, //    ###
	0xF8, 0x07, //    ########
	0xF8, 0x1F, //    ##########
	0x38, 0x1C, //    ###    ###
	0x38, 0x38, //    ###     ###
	0x38, 0x38, //    ###     ###
	0x38, 0x38, //    ###     ###
	0x38, 0x38, //    ###     ###
	0x38, 0x1C, //    ###    ###
	0xF8, 0x0F, //    #########
	0xF8, 0x03, //    #######

	// @1439 '�' (13 pixels wide)
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x07, 0x1C, // ###       ###
	0x7F, 0x1C, // #######   ###
	0xFF, 0x1C, // ########  ###
	0xE7, 0x1D, // ###  #### ###
	0xC7, 0x1D, // ###   ### ###
	0xC7, 0x1D, // ###   ### ###
	0xC7, 0x1D, // ###   ### ###
	0xC7, 0x1D, // ###   ### ###
	0xE7, 0x1C, // ###  ###  ###
	0xFF, 0x1C, // ########  ###
	0x3F, 0x1C, // ######    ###

	// @1473 '�' (12 pixels wide)
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0x07, 0x00, // ###
	0xFF, 0x01, // #########
	0xFF, 0x07, // ###########
	0x07, 0x07, // ###     ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x0E, // ###      ###
	0x07, 0x07, // ###     ###
	0xFF, 0x03, // ##########
	0xFF, 0x00, // ########

	// @1507 '�' (13 pixels wide)
	0xFE, 0x00, //  #######
	0xFF, 0x03, // ##########
	0x81, 0x07, // #      ####
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0xFE, 0x1F, //  ############
	0xFE, 0x1F, //  ############
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x1C, //           ###
	0x00, 0x0E, //          ###
	0x00, 0x0E, //          ###
	0x81, 0x07, // #      ####
	0xFF, 0x03, // ##########
	0xFE, 0x00, //  #######

	// @1541 '�' (14 pixels wide)
	0x87, 0x0F, // ###    #####
	0xC7, 0x1F, // ###   #######
	0xC7, 0x1D, // ###   ### ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xFF, 0x38, // ########   ###
	0xFF, 0x38, // ########   ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xE7, 0x38, // ###  ###   ###
	0xC7, 0x1D, // ###   ### ###
	0xC7, 0x1F, // ###   #######
	0x87, 0x0F, // ###    #####

	// @1575 '�' (12 pixels wide)
	0xF0, 0x0F, //     ########
	0xFC, 0x0F, //   ##########
	0x1C, 0x0E, //   ###    ###
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x0E, //  ###     ###
	0x0E, 0x0E, //  ###     ###
	0x1C, 0x0E, //   ###    ###
	0xFC, 0x0F, //   ##########
	0xF0, 0x0F, //     ########
	0x18, 0x0E, //    ##    ###
	0x0C, 0x0E, //   ##     ###
	0x0C, 0x0E, //   ##     ###
	0x0E, 0x0E, //  ###     ###
	0x06, 0x0E, //  ##      ###
	0x06, 0x0E, //  ##      ###
	0x07, 0x0E, // ###      ###*/

};
// Character descriptors for Consolas 20pt
// { [Char width in bits], [Offset into consolas_20ptCharBitmaps in bytes] }
FontChar_t consolas_20ptDescriptors[] =
{
	{13, 0}, 		// 0
	{11, 34}, 		// 1
	{11, 68}, 		// 2
	{11, 102}, 		// 3
	{14, 136}, 		// 4
	{11, 170}, 		// 5
	{12, 204}, 		// 6
	{12, 238}, 		// 7
	{12, 272}, 		// 8
	{13, 306}, 		// 9
	{4, 340}, 		// :
	{6, 353}, 		// ;
	{10, 371}, 		// <
	{11, 401}, 		// =
	{10, 415}, 		// >
	{9, 445}, 		// ?
	{15, 483}, 		// _
	{13, 487}, 		// �
	{12, 521}, 		// �
	{12, 555}, 		// �
	{10, 589}, 		// �
	{15, 623}, 		// �
	{10, 665}, 		// �
	{16, 699}, 		// �
	{12, 733}, 		// �
	{12, 767}, 		// �
	{12, 801}, 		// �
	{12, 845}, 		// �
	{13, 879}, 		// �
	{14, 913}, 		// �
	{12, 947}, 		// �
	{13, 981}, 		// �
	{12, 1015}, 		// �
	{12, 1049}, 		// �
	{12, 1083}, 		// �
	{13, 1117}, 		// �
	{12, 1151}, 		// �
	{15, 1185}, 		// �
	{15, 1219}, 		// �
	{13, 1253}, 		// �
	{13, 1295}, 		// �
	{13, 1329}, 		// �
	{14, 1363}, 		// �
	{14, 1405}, 		// �
	{13, 1439}, 		// �
	{12, 1473}, 		// �
	{13, 1507}, 		// �
	{14, 1541}, 		// �
	{12, 1575}, 		// �
	{12, 1587}, 		// end
};