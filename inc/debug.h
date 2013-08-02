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

#ifndef DEBUG_H_
#define DEBUG_H_

/***************************** Include Files *******************************/
#include <stdint.h>
#include <stdio.h>
/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/
/***************** Macros (Inline Functions) Definitions ********************/

/* Print messages to uart console */
#if 1
#	define	DEBUG_PRINTF(format, ...)   printf(format,## __VA_ARGS__)
#else
#	define DEBUG_PRINTF(...)
#endif /* _INCLUDE_DEBUG_ */

/* Print messages to soft uart console */
#if 1
#	define	DEBUG_PRINTF_SOFT(format, ...)   tx_print(format,## __VA_ARGS__)
#else
#	define DEBUG_PRINTF_SOFT(...)
#endif /* _INCLUDE_DEBUG_ */
/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/

extern void tx_print(char *s);
extern void tx_hexprint(char *s, char len);
#endif /* DEBUG_H_ */


