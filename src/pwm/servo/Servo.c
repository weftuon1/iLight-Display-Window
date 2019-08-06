#include "Servo.h"


Servo::Servo(){
    _angle = 0.0;
    _value = 0;
    _attached = False;
    _pwm_cfg->mode=DEV_PWM_TIMER_MODE_PWM;
    _pwm = pwm_timer_get_dev(IOTDK_PWM_ID);
}

void Servo::attach(uint32_t pin, uint32_t ch){
    io_arduino_config(pin, ARDUINO_PWM, IO_PINMUX_ENABLE);

    _ch=ch;
    _pin=pin;
    _attached=True;
    if (_pwm->pwm_timer_open() == E_OPNED)
	{
		_pwm->pwm_timer_control(ch, PWM_TIMER_CMD_ENA_CH, NULL);
	}
    _pwm ->pwm_timer_write(ch, _pwm_cfg->mode, REFRESH_FREQUENCY, DEFAULT_PULSE_WIDTH);
    //sys_msleep(10);//t ms
}

void Servo::write(double angle){
    if(!attached()){
        printf("Not attach yet");
    }else if(angle<0||angle>180){
        printf("angle is out of range");
    }else{
        _angle=angle;
        double rang = 180.0 / (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH);
        double duty = (angle) / rang + MIN_PULSE_WIDTH;
        _pwm ->pwm_timer_write(ch, _pwm_cfg->mode, REFRESH_FREQUENCY, duty);
    }
    
}

bool Servo::attached(){
    return _attached;
}

void Servo::detach(){
    if(!attached()){
        printf("Not attach yet");
    }else{
        _attached=False;
        pwm->pwm_timer_close();
    }
}
