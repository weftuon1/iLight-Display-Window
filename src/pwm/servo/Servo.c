#include "Servo.h"

void attach(uint32_t pin, uint32_t ch){
    int32_t statePWM = 0;
    _pwm_cfg->mode=DEV_PWM_TIMER_MODE_PWM;
    
    io_arduino_config(pin, ARDUINO_PWM, IO_PINMUX_ENABLE);
    _pwm = pwm_timer_get_dev(IOTDK_PWM_ID);
    _ch=ch;
    _pin=pin;
    _attached=true;

    statePWM=_pwm->pwm_timer_open();
    if (statePWM == E_OPNED)
	{
		_pwm->pwm_timer_control(ch, PWM_TIMER_CMD_ENA_CH, NULL);

	}else if(statePWM == E_OK){
        printf("Success\n");
    }

    /* statePWM=_pwm ->pwm_timer_write(ch, DEV_PWM_TIMER_MODE_PWM, REFRESH_FREQUENCY, DEFAULT_PULSE_WIDTH);//90 degree
    if(statePWM == E_OK){
        printf("Success \n");
    }else if(statePWM == E_OBJ){
        printf("E_OBJ\n");
    }else if(statePWM == E_PAR){
        printf("E_PAR\n");
    }else if(statePWM == E_SYS){
        printf("E_SYS\n");
    }*/
    board_delay_ms(10,1);

    /* uint32_t m;
    uint32_t f;
    uint32_t d;

    statePWM= _pwm->pwm_timer_read(ch, &(_pwm_cfg->mode), &f, &d);
    if(statePWM == E_OK){
        printf("Success\n");
    }else if(statePWM == E_OBJ){
        printf("E_OBJ\n");
    }else if(statePWM == E_PAR){
        printf("E_PAR\n");
    }else if(statePWM == E_SYS){
        printf("E_SYS\n");
    }else{
        printf("WTF\n");
    }*/

}
void write(double angle){
    if(!_attached){
        printf("Not attach yet");
    }else if(angle<0||angle>180){
        printf("angle is out of range");
    }else{

   
        _angle=angle;
        double rang = 180.0 / (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH);
        double dd=(angle) / rang + MIN_PULSE_WIDTH;
        uint32_t duty = dd;
 
       int32_t statePWM = 0;
        statePWM=_pwm ->pwm_timer_write(_ch, DEV_PWM_TIMER_MODE_PWM, REFRESH_FREQUENCY, duty);
        //sys_msleep(10);
        board_delay_ms(100,1);
        if(statePWM == E_OK){
            printf("Success %f, %d\n", dd, duty);
        }
    }
}
void detach(){
    if(!_attached){
        printf("Not attach yet");
    }else{
        _attached=false;
        _pwm->pwm_timer_close();
    }
}
/* Servo::Servo(){
    _angle = 0.0;
    //_value = 0;
    _attached = False;
    _pwm_cfg->mode=DEV_PWM_TIMER_MODE_PWM;
    _pwm = pwm_timer_get_dev(IOTDK_PWM_ID);
}*/

/* void Servo::attach(uint32_t pin, uint32_t ch){
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
}*/

/* void Servo::write(double angle){
    if(!attached()){
        printf("Not attach yet");
    }else if(angle<0||angle>180){
        printf("angle is out of range");
    }else{
        _angle=angle;
        double rang = 180.0 / (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH);
        double duty = (angle) / rang + MIN_PULSE_WIDTH;
        _pwm ->pwm_timer_write(_ch, _pwm_cfg->mode, REFRESH_FREQUENCY, duty);
    }
    
}*/

/* bool Servo::attached(){
    return _attached;
}

void Servo::detach(){
    if(!attached()){
        printf("Not attach yet");
    }else{
        _attached=False;
        _pwm->pwm_timer_close();
    }
}
*/