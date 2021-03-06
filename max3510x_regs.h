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

// RTC

#define MAX3510X_REG_SECONDS					0

#define MAX3510X_REG_SECONDS_TENTHS_SHIFT		12
#define MAX3510X_REG_SECONDS_TENTHS_WIDTH		4
#define MAX3510X_REG_SECONDS_HUNDREDTHS_SHIFT	8
#define MAX3510X_REG_SECONDS_HUNDREDTHS_WIDTH	4
#define MAX3510X_REG_SECONDS_10SECS_SHIFT		4
#define MAX3510X_REG_SECONDS_10SECS_WIDTH		4
#define MAX3510X_REG_SECONDS_1SECS_SHIFT		0
#define MAX3510X_REG_SECONDS_1SECS_WIDTH		4

#define MAX3510X_BF_GET(n,v)	((((uint16_t)(v)) >> ((uint8_t)MAX3510X_REG_##n##_SHIFT)) & (1<<(((uint8_t)MAX3510X_REG_##n##_WIDTH)-1)))
#define MAX3510X_BF_SET(n,v)	(((v) & (1<<(((uint8_t)MAX3510X_REG_##n##_WIDTH)-1))) << MAX3510X_REG_##n##_SHIFT)

#define MAX3510X_REG_MINS_HRS					1

#define MAX3510X_REG_MINS_HRS_10MINS_SHIFT		12
#define MAX3510X_REG_MINS_HRS_10MINS_WIDTH		3
#define MAX3510X_REG_MINS_HRS_1MINS_SHIFT		8
#define MAX3510X_REG_MINS_HRS_1MINS_WIDTH		4
#define MAX3510X_REG_MINS_HRS_12_24_SHIFT		6
#define MAX3510X_REG_MINS_HRS_12_24_WIDTH		1
#define MAX3510X_REG_MINS_HRS_12_24_MODE_12		1
#define MAX3510X_REG_MINS_HRS_12_24_MODE_24		0
#define MAX3510X_REG_MINS_HRS_20HR_AMPM_SHIFT	5
#define MAX3510X_REG_MINS_HRS_20HR_AMPM_WIDTH	1
#define MAX3510X_REG_MINS_HRS_20HR_AMPM_PM		1
#define MAX3510X_REG_MINS_HRS_20HR_AMPM_AM		0
#define MAX3510X_REG_MINS_HRS_10HR_SHIFT		4
#define MAX3510X_REG_MINS_HRS_10HR_WIDTH		1
#define MAX3510X_REG_MINS_HRS_HOURS_SHIFT		0
#define MAX3510X_REG_MINS_HRS_HOURS_WIDTH		4

#define MAX3510X_REG_DAY_DATE					2

#define MAX3510X_REG_DAY_DATE_DAY_SHIFT			8
#define MAX3510X_REG_DAY_DATE_DAY_WIDTH			3
#define MAX3510X_REG_DAY_DATE_10DATE_SHIFT		4
#define MAX3510X_REG_DAY_DATE_10DATE_WIDTH		2
#define MAX3510X_REG_DAY_DATE_DATE_SHIFT		0
#define MAX3510X_REG_DAY_DATE_DATE_WIDTH		4

#define MAX3510X_REG_MONTH_YEAR					3

#define MAX3510X_REG_MONTH_YEAR_MONTH_SHIFT		8
#define MAX3510X_REG_MONTH_YEAR_MONTH_WIDTH	4
#define MAX3510X_REG_MONTH_YEAR_10MONTH_SHIFT	12
#define MAX3510X_REG_MONTH_YEAR_10MONTH_WIDTH	1

#define MAX3510X_REG_MONTH_YEAR_YEAR_SHIFT		0
#define MAX3510X_REG_MONTH_YEAR_YEAR_WIDTH		4
#define MAX3510X_REG_MONTH_YEAR_10YEAR_SHIFT	4
#define MAX3510X_REG_MONTH_YEAR_10YEAR_WIDTH	4

#define MAX3510X_REG_WATCHDOG_ALARM_COUNTER		4
#define MAX3510X_REG_ALARM						5

#define MAX3510X_REG_TOF1						8
#define MAX3510X_REG_TOF2						9
#define MAX3510X_REG_TOF3						10
#define MAX3510X_REG_TOF4						11
#define MAX3510X_REG_TOF5						12
#define MAX3510X_REG_TOF6						13
#define MAX3510X_REG_TOF7						14
#define MAX3510X_REG_EVENT_TIMING_1				15
#define MAX3510X_REG_EVENT_TIMING_2				16
#define MAX3510X_REG_TOF_MEASUREMENT_DELAY		17
#define MAX3510X_REG_CALIBRATION_CONTROL		18
#define MAX3510X_REG_RTC						19

// following registers are read only

#define MAX3510X_REG_WVRUP						20
#define MAX3510X_REG_HIT1UPINT					21
#define MAX3510X_REG_HIT1UPFRAC					22
#define MAX3510X_REG_HIT2UPINT					23
#define MAX3510X_REG_HIT2UPFRAC					24
#define MAX3510X_REG_HIT3UPINT					25
#define MAX3510X_REG_HIT3UPFRAC					26
#define MAX3510X_REG_HIT4UPINT					27
#define MAX3510X_REG_HIT4UPFRAC					28
#define MAX3510X_REG_HIT5UPINT					29
#define MAX3510X_REG_HIT5UPFRAC					30
#define MAX3510X_REG_HIT6UPINT					31
#define MAX3510X_REG_HIT6UPFRAC					32

#define MAX3510X_REG_AVGUPINT					33
#define MAX3510X_REG_AVGUPFRAC					34

#define MAX3510X_REG_WVRDN						35
#define MAX3510X_REG_HIT1DNINT					36
#define MAX3510X_REG_HIT1DNFRAC					37
#define MAX3510X_REG_HIT2DNINT					38
#define MAX3510X_REG_HIT2DNFRAC					39
#define MAX3510X_REG_HIT3DNINT					40
#define MAX3510X_REG_HIT3DNFRAC					41
#define MAX3510X_REG_HIT4DNINT					42
#define MAX3510X_REG_HIT4DNFRAC					43
#define MAX3510X_REG_HIT5DNINT					44
#define MAX3510X_REG_HIT5DNFRAC					45
#define MAX3510X_REG_HIT6DNINT					46
#define MAX3510X_REG_HIT6DNFRAC					47

#define MAX3510X_REG_AVGDNINT					48
#define MAX3510X_REG_AVGDNFRAC					49

#define MAX3510X_REG_TOF_DIFFINT				50
#define MAX3510X_REG_TOF_DIFFFRAC				51
#define MAX3510X_REG_TOF_CYCLE_COUNT			52
#define MAX3510X_REG_TOF_DIFF_AVGINT			53
#define MAX3510X_REG_TOF_DIFF_AVGFRAC			54

#define MAX3510X_REG_T1INT						55
#define MAX3510X_REG_T1FRAC						56
#define MAX3510X_REG_T2INT						57
#define MAX3510X_REG_T2FRAC						58
#define MAX3510X_REG_T3INT						59
#define MAX3510X_REG_T3FRAC						60
#define MAX3510X_REG_T4INT						61
#define MAX3510X_REG_T4FRAC						62

#define MAX3510X_REG_TEMP_CYCLE_COUNT			63
#define MAX3510X_REG_T1_AVGINT					64
#define MAX3510X_REG_T1_AVGFRAC					65
#define MAX3510X_REG_T2_AVGINT					66
#define MAX3510X_REG_T2_AVGFRAC					67
#define MAX3510X_REG_T3_AVGINT					68
#define MAX3510X_REG_T3_AVGFRAC					69
#define MAX3510X_REG_T4_AVGINT					70
#define MAX3510X_REG_T4_AVGFRAC					71

#define MAX3510X_REG_CALIBRATIONINT				72
#define MAX3510X_REG_CALIBRATIONFRAC			73

#define MAX3510X_REG_INTERRUPT_STATUS			78

#define MAX3510X_REG_INTERRUPT_STATUS_TO		(1<<15)
#define MAX3510X_REG_INTERRUPT_STATUS_AF		(1<<14)
#define MAX3510X_REG_INTERRUPT_STATUS_TOF		(1<<12)
#define MAX3510X_REG_INTERRUPT_STATUS_TE		(1<<11)
#define MAX3510X_REG_INTERRUPT_STATUS_LDO		(1<<10)
#define MAX3510X_REG_INTERRUPT_STATUS_TOF_EVTMG	(1<<9)
#define MAX3510X_REG_INTERRUPT_STATUS_TEMP_EVTMG (1<<8)
#define MAX3510X_REG_INTERRUPT_STATUS_FLASH		(1<<7)
#define MAX3510X_REG_INTERRUPT_STATUS_CAL		(1<<6)
#define MAX3510X_REG_INTERRUPT_STATUS_HALT		(1<<5)
#define MAX3510X_REG_INTERRUPT_STATUS_CSWI		(1<<4)
#define MAX3510X_REG_INTERRUPT_STATUS_INIT		(1<<3)
#define MAX3510X_REG_INTERRUPT_STATUS_POR		(1<<2)



#define MAX3510X_REG_CONTROL					79


