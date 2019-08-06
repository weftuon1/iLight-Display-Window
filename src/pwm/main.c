/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

/**
 * \defgroup	EMBARC_APP_TMPL		embARC Template Example
 * \ingroup	EMBARC_APPS_TOTAL
 * \ingroup	EMBARC_APPS_BOARD_EMSK
 * \ingroup	EMBARC_APPS_BAREMETAL
 * \brief	embARC Example for template
 *
 * \details
 * ### Extra Required Tools
 *
 * ### Extra Required Peripherals
 *
 * ### Design Concept
 *
 * ### Usage Manual
 *
 * ### Extra Comments
 *
 */

/**
 * \file
 * \ingroup	EMBARC_APP_TMPL
 * \brief	main source of template example
 */

/**
 * \addtogroup	EMBARC_APP_TMPL
 * @{
 */
/* embARC HAL */
#include "embARC.h"
#include "embARC_debug.h"
#include <stdio.h>

#define PWM_TIMER_0_CH_MAX_COUNT    DW_PWM_TIMER_0_CH_MAX_COUNT
#define IOTDK_PWM_ID		        DW_PWM_TIMER_0_ID
#define IOTDK_PWM_CH_0		        0
#define IOTDK_PWM_FREQ		        50

#define COUNT BOARD_CPU_CLOCK/1000

volatile static int t0 = 0;
volatile static int second = 1;

/** arc timer 0 interrupt routine */
static void timer0_isr(void *ptr)
{
	timer_int_clear(TIMER_0);
	t0++;
}

/** arc timer 0 interrupt delay */
void timer0_delay_ms(int ms)
{
	t0 = 0;
	while(t0 < ms);
}

/** main entry */
int main(void)
{

    DEV_PWM_TIMER_PTR       pwm_ch_0;
    DEV_PWM_TIMER_CFG_PTR   pwm_cfg;

    pwm_cfg->mode=DEV_PWM_TIMER_MODE_PWM;

    io_arduino_config(ARDUINO_PIN_3, ARDUINO_PWM, IO_PINMUX_ENABLE);
    pwm_ch_0 = pwm_timer_get_dev(IOTDK_PWM_ID);

    if (pwm_ch_0->pwm_timer_open() == E_OPNED)
	{
        
		pwm_ch_0->pwm_timer_control(IOTDK_PWM_CH_0, PWM_TIMER_CMD_ENA_CH, NULL);
	}
    int dc=50;
    int gap=-1;
    //printf("1 %d\r\n", dc);
	while(1){
        //

        pwm_ch_0->pwm_timer_write(IOTDK_PWM_CH_0, pwm_cfg->mode, IOTDK_PWM_FREQ, dc);
         dc=dc+gap;
        if(dc==0){
            gap=1;
        }else if(dc==100){
            gap=-1;
        }
        //printf("2 %d\r\n", dc);
        //timer0_delay_ms(1000);//not working
        //printf("3 %d\r\n", dc);
    }
        //duty cycle max: 100
        
    pwm_ch_0->pwm_timer_close();

	
	return E_SYS;
}

/** @} */