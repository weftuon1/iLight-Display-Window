#include    "led_pwm.h"



void set_pwm_ch_0(double duty){

    io_arduino_config(IOTDK_PWM_CH_0_PIN, ARDUINO_PWM, IO_PINMUX_ENABLE);
    pwm_ch_0 = pwm_timer_get_dev(IOTDK_PWM_ID);

    if (pwm_ch_0->pwm_timer_open() == E_OPNED)
	{        
		pwm_ch_0->pwm_timer_control(IOTDK_PWM_CH_0, PWM_TIMER_CMD_ENA_CH, NULL);
	}

    uint32_t int_duty;
    int_duty=duty;

    pwm_ch_0->pwm_timer_write(IOTDK_PWM_CH_0, DEV_PWM_TIMER_MODE_PWM, IOTDK_PWM_FREQ, int_duty);

        //duty cycle max: 100
        
    pwm_ch_0->pwm_timer_close();
}