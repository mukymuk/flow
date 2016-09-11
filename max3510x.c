/*******************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 ******************************************************************************/

#include "max3510x.h"

// The MAX3510x uses SPI Mode 1 (SCK low, negative edge)


#define MAX3510X_SPIM					MXC_SPIM1

#define MAX3510X_OPCODE_TOF_UP			0x00
#define MAX3510X_OPCODE_TOF_DOWN		0x01
#define MAX3510X_OPCODE_TOF_DIFF		0x02
#define MAX3510X_OPCODE_TEMPERATURE		0x03
#define MAX3510X_OPCODE_RESET			0x04
#define MAX3510X_OPCODE_INITIALIZE		0x05
#define MAX3510X_OPCODE_FLASH			0x06
#define MAX3510X_OPCODE_EVTMG1			0x07
#define MAX3510X_OPCODE_EVTMG2			0x08
#define MAX3510X_OPCODE_EVTMG3			0x09
#define MAX3510X_OPCODE_HALT			0x0A
#define MAX3510X_OPCODE_LDO_TIMED		0x0B
#define MAX3510X_OPCODE_LDO_ON			0x0C
#define MAX3510X_OPCODE_LDO_OFF			0x0D
#define MAX3510X_OPCODE_CALIBRATE		0x0E

#define MAX3510X_OPCODE_READ_BASE		0xB0
#define MAX3510X_OPCODE_READ_REG(r)		(MAX3510X_OPCODE_READ_BASE+(r))

#define MAX3510X_OPCODE_WRITE_BASE		0x30
#define MAX3510X_OPCODE_WRITE_REG(r)	(MAX3510X_OPCODE_WRITE_BASE+(r))

#define MAX3510X_OPCODE_READ_FLASH		0x90
#define MAX3510X_OPCODE_WRITE_FLASH		0x10
#define MAX3510X_OPCODE_ERASE_FLASH		0x13


void max3510x_init( void )
{
}
