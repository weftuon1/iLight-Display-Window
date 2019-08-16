#ifndef _LIGHT_SENSOR_H_
#define _LIGHT_SENSOR_H_


ADC_DEFINE(adc_test, ADC_INT_NUM, ADC_CRTL_BASE, NULL);

void arduino_pin_init(void);

uint16_t get_lightness(uint8_t id);

#endif