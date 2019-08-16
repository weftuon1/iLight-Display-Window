#ifndef _SERVO_H_
#define _SERVO_H_

#include "embARC.h"
#include "embARC_debug.h"
#include <stdio.h>
#include <math.h>

#define SREEN_WIDTH_MID         240.00//480/2
#define SREEN_HEIGHT_MID        180.00//360/2
#define SREEN_WIDTH             480.00//480/2
#define SREEN_HEIGHT            360.00//360/2
#define LENGTH_2_OBJ            1000.00

#define PI                      3.14

#define MIN_PULSE_WIDTH         544   //   0 degrees: 0.544 ms
#define DEFAULT_PULSE_WIDTH     1500    //  90 degrees: 1.500 ms
#define MAX_PULSE_WIDTH         2400    // 180 degrees: 2.400 ms

#define V_DEG_OFFSET            18

#define SIGNAL_PERIOD           20000    

#define IOTDK_PWM_ID_0		    DFSS_GPIO_4B2_ID
#define IOTDK_PWM_ID_1		    DFSS_GPIO_8B2_ID

static double   _angle;
static bool     _attached;
static uint32_t _bit;

static DEV_GPIO_PTR _gpio_pwm;

void attach(uint32_t pin, uint32_t id, uint32_t bit);
void write(double angle);
void detach();

double X2Deg(uint32_t x);
double Y2Deg(uint32_t y);

#endif