#include "Servo.h"

void attach(uint32_t pin, uint32_t id, uint32_t bit){

	io_arduino_config(pin, ARDUINO_GPIO, IO_PINMUX_ENABLE);

	_gpio_pwm = gpio_get_dev(id);

    int32_t statePWM = 0;
    statePWM=_gpio_pwm->gpio_open((1 << bit));
	if ( statePWM== E_OPNED)
	{
        printf("opened\r\n");
		_gpio_pwm->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT,
								(void *)(1 << bit));
	}else if(statePWM==E_OK){
        printf("successed\r\n");
    }

	for(int i=0;i<100;i++)
	{
		_gpio_pwm->gpio_write(1 << bit, 1 << bit);
        //board_delay_ms(100,1);
		arc_delay_us(DEFAULT_PULSE_WIDTH);
		_gpio_pwm->gpio_write(0, 1 << bit);
		arc_delay_us(SIGNAL_PERIOD-DEFAULT_PULSE_WIDTH);
	}

    _bit=bit;
    _attached=true;
    board_delay_ms(10,1);
}

void write(double angle){
    if(!_attached){
        printf("Not attach yet");
    }else if(angle<0||angle>180){
        printf("angle is out of range");
    }else{       
        _angle=angle;
        double rang = 180.0 / (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH);
        double width=(angle) / rang + MIN_PULSE_WIDTH;

        //printf("width=%f", width);
        uint32_t W=width;
        for(int i=0;i<100;i++)
        {
            _gpio_pwm->gpio_write(1 << _bit, 1 << _bit);
            arc_delay_us(W);
            _gpio_pwm->gpio_write(0, 1 << _bit);
            arc_delay_us(SIGNAL_PERIOD-W);
        }        
        
        board_delay_ms(10,1);
    }
}
void detach(){
    if(!_attached){
        printf("Not attach yet");
    }else{
        _attached=false;
        _gpio_pwm->gpio_close();
    }
}

double W2Deg(uint32_t w){
    return 90;
}

double H2Deg(uint32_t h){
    return 90;
}

