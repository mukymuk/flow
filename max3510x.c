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

#include "global.h"
#include "max3510x.h"
#include "max3510x_regs.h"
#include "spim.h"


static void spi_xfer( void *pv_in, const void *pv_out, uint8_t count )
{
	spim_req_t req;
	req.ssel = 0;
	req.deass = 1;
	req.tx_data = pv_out;
	req.rx_data = pv_in;
	req.width = SPIM_WIDTH_1;
	req.len = count;

	if( SPIM_Trans(MXC_SPIM0, &req) != count )
	{
		while( 1 );
	}

	// Wait for transaction to complete
	while( SPIM_Busy(MXC_SPIM0) != E_NO_ERROR )
	{
	}
}

static void send_opcode( uint8_t code )
{
	spi_xfer(NULL, &code, sizeof(code));
}

static uint8_t rtc_get_year( uint16_t reg_value )
{
	uint8_t year = MAX3510X_BF_GET(MONTH_YEAR_YEAR, reg_value);
	year += MAX3510X_BF_GET(MONTH_YEAR_10YEAR, reg_value) * 10;
	return year;
}

static uint16_t rtc_set_year( uint8_t year )
{
	return MAX3510X_BF_GET(MONTH_YEAR_YEAR, year % 10) | MAX3510X_BF_GET(MONTH_YEAR_10YEAR, year / 10);
}

static uint8_t rtc_get_month( uint16_t reg_value )
{
	uint8_t month = MAX3510X_BF_GET(MONTH_YEAR_MONTH, reg_value);
	month += MAX3510X_BF_GET(MONTH_YEAR_10MONTH, reg_value) * 10;
	return month;
}

static uint16_t rtc_set_month( uint8_t month )
{
	return MAX3510X_BF_GET(MONTH_YEAR_10MONTH, month / 10) | MAX3510X_BF_GET(MONTH_YEAR_MONTH, month % 10);
}

static uint8_t rtc_get_day_of_month( uint16_t reg_value )
{
	uint8_t day_of_month = MAX3510X_BF_GET(DAY_DATE_10DATE, reg_value);
	day_of_month += MAX3510X_BF_GET(DAY_DATE_DATE, reg_value);
	return day_of_month;
}

static uint16_t rtc_set_day_of_month( uint8_t day_of_month )
{
	return MAX3510X_BF_GET(DAY_DATE_DATE, day_of_month);
}

static uint8_t rtc_get_day_of_week( uint16_t reg_value )
{
	return MAX3510X_BF_GET(DAY_DATE_DAY, reg_value);
}

static uint16_t rtc_set_day_of_week( uint8_t day_of_week )
{
	return MAX3510X_BF_SET(DAY_DATE_DAY, day_of_week);
}

static uint8_t rtc_get_hours( uint16_t reg_value )
{
	// returns 0-24

	uint8_t hours = MAX3510X_BF_GET(MINS_HRS_HOURS, reg_value);
	if( MAX3510X_BF_GET(MINS_HRS_12_24, reg_value) == MAX3510X_REG_MINS_HRS_12_24_MODE_12 )
	{
		// 12 hour mode.
		if( MAX3510X_BF_GET(MINS_HRS_20HR_AMPM, reg_value) == MAX3510X_REG_MINS_HRS_20HR_AMPM_PM )
		{
			// PM
			hours += 12;
		}
	}
	else
	{
		// 24 hour mode.
		if( MAX3510X_BF_GET(MINS_HRS_20HR_AMPM, reg_value) )
		{
			hours += 20;
		}
	}
	if( MAX3510X_BF_GET(MINS_HRS_10HR, reg_value) )
	{
		hours += 10;
	}
	return hours;
}

static uint16_t rtc_set_hour( uint8_t hour )
{
	uint16_t reg_value = 0;
	if( hour > 19 )
	{
		reg_value |= MAX3510X_BF_SET(MINS_HRS_20HR_AMPM, 1);
		hour -= 20;
	}
	if( hour > 9 )
	{
		reg_value |= MAX3510X_BF_SET(MINS_HRS_10HR, 1);
		hour -= 20;
	}
	reg_value |= MAX3510X_BF_SET(MINS_HRS_HOURS, hour);
	return reg_value;
}

static uint8_t rtc_get_minutes( uint16_t reg_value )
{
	uint8_t minutes = MAX3510X_BF_GET(MINS_HRS_10MINS, reg_value) * 10;
	minutes += MAX3510X_BF_GET(MINS_HRS_1MINS, reg_value);
	return minutes;
}

static uint16_t rtc_set_minutes( uint8_t minutes )
{
	return MAX3510X_BF_SET(MINS_HRS_10MINS, minutes / 10) | MAX3510X_BF_SET(MINS_HRS_1MINS, minutes % 10);
}

static uint8_t rtc_get_seconds( uint16_t reg_value )
{
	uint8_t seconds = MAX3510X_BF_GET(SECONDS_10SECS, reg_value) * 10;
	seconds += MAX3510X_BF_GET(SECONDS_1SECS, reg_value);
	return seconds;
}

static uint16_t rtc_set_seconds( uint8_t seconds )
{
	return MAX3510X_BF_SET(SECONDS_10SECS, seconds / 10) | MAX3510X_BF_SET(SECONDS_1SECS, seconds % 10);
}

static uint8_t rtc_get_hundredths( uint16_t reg_value )
{
	uint8_t hundredths = MAX3510X_BF_GET(SECONDS_TENTHS, reg_value) * 10;
	hundredths += MAX3510X_BF_GET(SECONDS_HUNDREDTHS, reg_value);
	return hundredths;
}

static uint16_t rtc_set_hundredths( uint8_t hundredths )
{
	uint8_t tenths = hundredths / 10;
	uint8_t remainder = hundredths % 10;
	return MAX3510X_BF_SET(SECONDS_HUNDREDTHS, remainder) | MAX3510X_BF_SET(SECONDS_TENTHS, tenths);
}


void max3510x_rtc_get( rtc_date_t *p_date, const void *pv_rtc_data )
{
	const uint16_t *p_rtc_data = (const uint16_t *)pv_rtc_data;
	p_date->year = rtc_get_year(p_rtc_data[MAX3510X_REG_MONTH_YEAR]);
	p_date->month = rtc_get_month(p_rtc_data[MAX3510X_REG_MONTH_YEAR]);
	p_date->day_of_month = rtc_get_day_of_month(p_rtc_data[MAX3510X_REG_DAY_DATE]);
	p_date->day_of_week = rtc_get_day_of_week(p_rtc_data[MAX3510X_REG_DAY_DATE]);
	p_date->hour = rtc_get_hours(p_rtc_data[MAX3510X_REG_MINS_HRS]);
	p_date->minute = rtc_get_minutes(p_rtc_data[MAX3510X_REG_MINS_HRS]);
	p_date->seconds = rtc_get_seconds(p_rtc_data[MAX3510X_REG_SECONDS]);
	p_date->hundredths = rtc_get_hundredths(p_rtc_data[MAX3510X_REG_SECONDS]);
}

void max3510x_rtc_set( uint16_t *p_rtc_data, const rtc_date_t *p_date )
{
	p_rtc_data[MAX3510X_REG_SECONDS] = rtc_set_hundredths(p_date->hundredths) | rtc_set_seconds(p_date->seconds);
	p_rtc_data[MAX3510X_REG_MINS_HRS] = rtc_set_minutes(p_date->minute) | rtc_set_hour(p_date->hour);
	p_rtc_data[MAX3510X_REG_DAY_DATE] = rtc_set_day_of_week(p_date->day_of_week) | rtc_set_day_of_month(p_date->day_of_month);
	p_rtc_data[MAX3510X_REG_MONTH_YEAR] = rtc_set_month(p_date->month) | rtc_set_year(p_date->year);
}

#define MAX3510X_RTC_SIZE	9

void max3510x_init( void )
{
	rtc_date_t rtc_date;

	uint8_t rtc[MAX3510X_RTC_SIZE + 1];
	rtc[0] = MAX3510X_OPCODE_READ_REG(MAX3510X_REG_SECONDS);
	spi_xfer(NULL, rtc, sizeof(rtc));
	max3510x_rtc_get(&rtc_date, &rtc[1]);
}

void max3510x_isr( void *p )
{
}


void max3510x_tof_up( void )
{
	send_opcode(MAX3510X_OPCODE_TOF_UP);
}

void max3510x_tof_down( void )
{
	send_opcode(MAX3510X_OPCODE_TOF_DOWN);
}

void max3510x_tof_diff( void )
{
	send_opcode(MAX3510X_OPCODE_TOF_DIFF);
}

void max3510x_temperature( void )
{
	send_opcode(MAX3510X_OPCODE_TEMPERATURE);
}

void max3510x_reset( void )
{
	send_opcode(MAX3510X_OPCODE_RESET);
}

void max3510x_initialize( void )
{
	send_opcode(MAX3510X_OPCODE_INITIALIZE);
}

void max3510x_flash_configuration( void )
{
	send_opcode(MAX3510X_OPCODE_FLASH);
}

void max3510x_event_timing( max3510x_event_timing_mode_t mode )
{
	uint8_t opcode;
	switch( mode )
	{
		case max3510x_event_timing_mode_1:
			opcode = MAX3510X_OPCODE_EVTMG1;
			break;
		case max3510x_event_timing_mode_2:
			opcode = MAX3510X_OPCODE_EVTMG2;
			break;
		case max3510x_event_timing_mode_3:
			opcode = MAX3510X_OPCODE_EVTMG3;
			break;
		default:
			return;
	}
	send_opcode(opcode);
}

void max3510x_halt( void )
{
	send_opcode(MAX3510X_OPCODE_HALT);
}


void max3510x_ldo( max3510x_ldo_mode_t mode )
{ 
	uint8_t opcode;
	switch( mode )
	{
		case max3510x_ldo_mode_timed:
			opcode = MAX3510X_OPCODE_LDO_TIMED;
			break;
		case max3510x_ldo_mode_on:
			opcode = MAX3510X_OPCODE_LDO_ON;
			break;
		case max3510x_ldo_mode_off:
			opcode = MAX3510X_OPCODE_LDO_OFF;
			break;
		default:
			return;
	}
	send_opcode(opcode);
}

void max3510x_calibrate( void )
{
	send_opcode(MAX3510X_OPCODE_CALIBRATE);
}
