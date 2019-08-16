#include    "light_sensor.h"

void arduino_pin_init(void)
{
	io_arduino_config(ARDUINO_PIN_AD0, ARDUINO_ADC, IO_PINMUX_ENABLE);
	io_arduino_config(ARDUINO_PIN_AD1, ARDUINO_ADC, IO_PINMUX_ENABLE);
	io_arduino_config(ARDUINO_PIN_AD2, ARDUINO_ADC, IO_PINMUX_ENABLE);
	io_arduino_config(ARDUINO_PIN_AD3, ARDUINO_ADC, IO_PINMUX_ENABLE);
	io_arduino_config(ARDUINO_PIN_AD4, ARDUINO_ADC, IO_PINMUX_ENABLE);
	io_arduino_config(ARDUINO_PIN_AD5, ARDUINO_ADC, IO_PINMUX_ENABLE);
}

uint16_t get_lightness(uint8_t id)
{
    arduino_pin_init();
    

	uint16_t adc_value;
	arduino_pin_init();

	smic_adc_open(adc_test);

    smic_adc_read_polling(adc_test, id, &(adc_value));

    return adc_value;

}