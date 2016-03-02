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
* @file debug.h
*
* Put short file description here  !
*
 *  Created on: 02.08.2013
 *      Author: mollex
*
******************************************************************************/

#ifndef RC5_C_
#define RC5_C_

/***************************** Include Files *******************************/

/************************** Constant Definitions ****************************/

#define IR_COM_0		(0)
#define IR_COM_1		(1)
#define IR_COM_2		(2)
#define IR_COM_3		(3)
#define IR_COM_4		(4)
#define IR_COM_5		(5)
#define IR_COM_6		(6)
#define IR_COM_7		(7)
#define IR_COM_8		(8)
#define IR_COM_9		(9)
#define IR_COM_PLUS		(10)
#define IR_COM_MINUS	(11)
#define IR_COM_ON		(12)
#define IR_COM_PP		(14)
#define IR_COM_RIGHT	(16)
#define IR_COM_LEFT		(17)
#define IR_COM_UP		(32)
#define IR_COM_DOWN		(33)
#define IR_COM_YELLOW	(50)
#define IR_COM_BLUE		(52)
#define IR_COM_GREEN	(54)
#define IR_COM_RED		(55)
#define IR_COM_AV		(56)
#define IR_COM_OK		(59)

#define IR_COM_CROSS	(45)
#define IR_COM_TV		(60)

#define IR_COM_PIP		(0x26)
#define IR_COM_ESC		(0x3F) // Vitiaz - esc  VDS - tv

//VSD

#define IR_COM_VSD_PtoP		(34)// dot
#define IR_COM_VSD_MENU		(48)
#define IR_COM_VSD_DOUBLE_LEFT		(21)
#define IR_COM_VSD_DOUBLE_RIGHT		(22)

/**************************** Type Definitions ******************************/
/***************** Macros (Inline Functions) Definitions ********************/
/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/

void rc5Init();
unsigned char  rc5GetCmd(unsigned char  *outPtr);

#endif /* RC5_C_ */
