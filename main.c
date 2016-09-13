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
#include "mxc_config.h"
#include "led.h"
#include "nhd12832.h"
#include "tmr_utils.h"
#include "max3510x.h"

static const ioman_cfg_t ioman_cfg = IOMAN_SPIM0(IOMAN_MAP_A, 1, 1, 0, 0, 0, 0, 0);
static const gpio_cfg_t max3510x_rst = { PORT_2, PIN_0, GPIO_FUNC_GPIO, GPIO_PAD_NORMAL };
static const gpio_cfg_t max3510x_int = { PORT_2, PIN_1, GPIO_FUNC_GPIO, GPIO_PAD_INPUT_PULLUP };
static const gpio_cfg_t max3510x_wdo = { PORT_2, PIN_2, GPIO_FUNC_GPIO, GPIO_PAD_INPUT_PULLUP };


int main(void)
{
    printf("Flow Testbed\n");
/*
    SYS_IOMAN_UseVDDIOH(&max3510x_rst);
    SYS_IOMAN_UseVDDIOH(&max3510x_int);
    SYS_IOMAN_UseVDDIOH(&max3510x_wdo);

    GPIO_OutSet(&max3510x_rst);
    GPIO_Config(&max3510x_rst);
	GPIO_OutClr(&max3510x_rst);
    GPIO_Config(&max3510x_int);
	GPIO_Config(&max3510x_wdo);

    CLKMAN_SetClkScale(CLKMAN_CLK_SPIM2, CLKMAN_SCALE_DIV_2);

    IOMAN_Config(&ioman_cfg);

    GPIO_IntDisable(&max3510x_rst);
    GPIO_IntConfig(&max3510x_rst, GPIO_INT_HIGH_LEVEL);  
    GPIO_RegisterCallback(&max3510x_rst, max3510x_isr, NULL);
    NVIC_EnableIRQ(MXC_GPIO_GET_IRQ(max3510x_rst.port));
*/
    // Print to the OLED
    NHD12832_Init();
    NHD12832_ShowString((uint8_t*)"Flow Testbed", 0, 4);

	GPIO_OutSet(&max3510x_rst);

    int count = 0;
    while(1) {
        LED_On(0);
        TMR_Delay(MXC_TMR0, MSEC(500));
        LED_Off(0);
        TMR_Delay(MXC_TMR0, MSEC(500));
        printf("count = %d\n", count++);
    }
}
