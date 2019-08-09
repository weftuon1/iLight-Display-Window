#ifndef _SERVO_H_
#define _SERVO_H_

#include "embARC.h"
#include "embARC_debug.h"
#include <stdio.h>

//#include "sys.h"

// If you double the PWM freqnency, you also have to double the three
    // pulse width parameters
#define   REFRESH_FREQUENCY    400//50*5
#define   MIN_PULSE_WIDTH      22//2.72*5    //   0 degrees: 0.544 ms
#define   DEFAULT_PULSE_WIDTH  60//7.50*5     //  90 degrees: 1.500 ms
#define   MAX_PULSE_WIDTH      96//12.00*5     // 180 degrees: 2.400 ms

#define IOTDK_PWM_ID		        DW_PWM_TIMER_0_ID

double _angle;
bool _attached;
uint32_t _pin;
uint32_t _ch;
DEV_PWM_TIMER_PTR       _pwm;
DEV_PWM_TIMER_CFG_PTR   _pwm_cfg;


/* typedef struct servo{
    double angle;

    bool attached;
    uint32_t pin;
    uint32_t ch;
    DEV_PWM_TIMER_PTR       pwm;
    DEV_PWM_TIMER_CFG_PTR   pwm_cfg;

}SERVO, *SERVO_PTR;*/


void attach(uint32_t pin, uint32_t ch);
void write(double angle);
void detach();

/* Class Servo{
    private:
        double _angle;
        //int _val;
        bool _attached;
        uint32_t _pin;
        uint32_t _ch;
        DEV_PWM_TIMER_PTR       _pwm;
        DEV_PWM_TIMER_CFG_PTR   _pwm_cfg;

    public:
        Servo();
        void attach(uint32_t pin, uint32_t ch);
        void write(double angle);
        bool attached();
        void detach();
};*/

#endif