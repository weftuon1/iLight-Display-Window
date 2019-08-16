#include "Servo.h"

void attach(uint32_t pin, uint32_t id, uint32_t bit){

	io_arduino_config(pin, ARDUINO_GPIO, IO_PINMUX_ENABLE);

	_gpio_pwm = gpio_get_dev(id);

    int32_t statePWM = 0;
    statePWM=_gpio_pwm->gpio_open((1 << bit));
	if ( statePWM== E_OPNED)
	{
        //printf("opened\r\n");
		_gpio_pwm->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT,
								(void *)(1 << bit));
	}else if(statePWM==E_OK){
        //printf("successed\r\n");
    }

	/*for(int i=0;i<100;i++)
	{
		_gpio_pwm->gpio_write(1 << bit, 1 << bit);
        //board_delay_ms(100,1);
		arc_delay_us(DEFAULT_PULSE_WIDTH);
		_gpio_pwm->gpio_write(0, 1 << bit);
		arc_delay_us(SIGNAL_PERIOD-DEFAULT_PULSE_WIDTH);
	}*/

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

double X2Deg(uint32_t x){
    double deg;
    double dbl_x = x;

    if(x < SREEN_WIDTH_MID){
        //if(x<0)x=0;
        deg=atan((SREEN_WIDTH_MID-dbl_x)/LENGTH_2_OBJ)/PI*180;
        printf("deg=%f\r\n", deg);
        return 90+deg;
    }else{
        if(x>SREEN_WIDTH)x=SREEN_WIDTH;
        deg=atan((dbl_x-SREEN_WIDTH_MID)/LENGTH_2_OBJ)/PI*180;
        printf("deg=%f\r\n", deg);
        return 90-deg;
    }
    //return 90;
}

double Y2Deg(uint32_t y){
    double deg;
    double dbl_y = y;

    if(y < SREEN_HEIGHT_MID){
        //if(y<0)y=0;
        deg=atan((SREEN_HEIGHT_MID-dbl_y)/LENGTH_2_OBJ)/PI*180;
        printf("deg=%f\r\n", deg);
        return 90-deg-V_DEG_OFFSET;
    }else{
        if(y>SREEN_HEIGHT)y=SREEN_HEIGHT;
        deg=atan((dbl_y-SREEN_HEIGHT_MID)/LENGTH_2_OBJ)/PI*180;
        printf("deg=%f\r\n", deg);
        return 90+deg-V_DEG_OFFSET;
    }
}

