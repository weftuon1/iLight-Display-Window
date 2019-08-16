#ifndef _LED_PWM_H_
#define _LED_PWM_H_

#include "embARC.h"
//#include "embARC_debug.h"
#include <stdio.h>

#define PWM_TIMER_0_CH_MAX_COUNT    DW_PWM_TIMER_0_CH_MAX_COUNT
#define IOTDK_PWM_ID		        DW_PWM_TIMER_0_ID
#define IOTDK_PWM_CH_0		        0
#define IOTDK_PWM_CH_1		        1
#define IOTDK_PWM_CH_2		        2
#define IOTDK_PWM_CH_3		        3
#define IOTDK_PWM_CH_4		        4
#define IOTDK_PWM_CH_5		        5
#define IOTDK_PWM_CH_0_PIN			ARDUINO_PIN_3
#define IOTDK_PWM_CH_1_PIN		    ARDUINO_PIN_5
#define IOTDK_PWM_CH_2_PIN		    ARDUINO_PIN_6
#define IOTDK_PWM_CH_3_PIN		    ARDUINO_PIN_9
#define IOTDK_PWM_CH_4_PIN		    ARDUINO_PIN_10
#define IOTDK_PWM_CH_5_PIN		    ARDUINO_PIN_11
#define IOTDK_PWM_FREQ		        2180//2180

static  DEV_PWM_TIMER_PTR       pwm_ch_0;

void set_pwm_ch_0(double duty);

#endif