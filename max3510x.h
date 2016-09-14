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

typedef struct _rtc_date_t
{
	uint8_t	year;
	uint8_t month;
	uint8_t day_of_month;
	uint8_t day_of_week;
	uint8_t hour;
	uint8_t minute;
	uint8_t seconds;
	uint8_t hundredths;
}
rtc_date_t;

typedef enum 
{
    max3510x_event_timing_mode_1,
    max3510x_event_timing_mode_2,
    max3510x_event_timing_mode_3
}
max3510x_event_timing_mode_t;

typedef enum
{
	max3510x_ldo_mode_timed,
	max3510x_ldo_mode_on,
	max3510x_ldo_mode_off
}
max3510x_ldo_mode_t;

void max3510x_isr(void*);
void max3510x_init(void);
void max3510x_tof_up(void);
void max3510x_tof_down(void);
void max3510x_tof_diff(void);
void max3510x_temperature(void);
void max3510x_reset( void );
void max3510x_initialize( void );
void max3510x_flash_configuration( void );
void max3510x_event_timing( max3510x_event_timing_mode_t mode );
void max3510x_halt( void );
void max3510x_ldo( max3510x_ldo_mode_t mode );
void max3510x_calibrate( void );
