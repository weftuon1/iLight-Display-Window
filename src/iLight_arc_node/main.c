#include "myuart.h"
#include "Servo.h"

#define IOTDK_PWM_0_BIT			2
#define IOTDK_PWM_1_BIT		    0

#define IOTDK_GPIO_PWM_ID_0		DFSS_GPIO_4B2_ID
#define IOTDK_GPIO_PWM_ID_1		DFSS_GPIO_8B2_ID
#define IOTDK_GPIO_PWM_PIN_0	ARDUINO_PIN_2
#define IOTDK_GPIO_PWM_PIN_1	ARDUINO_PIN_4

/** main entry */
int main(void)
{
	/*vertical horizon*/
	double deg_v, deg_h;

	UartEnable();

	UartSend("hihi from ARC\r\n", 15);
	processTransmit();
	while(1){		
		/*read darkest location from RPi*/
		processReceiveFromRPi();		
printf("transfering...\r\n");
		/*location to degree*/
		deg_h=W2Deg(get_width());
		deg_v=H2Deg(get_height());
printf("writing...\r\n");
		/*write degree to servo*/
		attach(IOTDK_GPIO_PWM_PIN_0, IOTDK_GPIO_PWM_ID_0, IOTDK_PWM_0_BIT);
		write(deg_v);
		detach();
		attach(IOTDK_GPIO_PWM_PIN_1, IOTDK_GPIO_PWM_ID_1, IOTDK_PWM_1_BIT);
		write(deg_h);
		detach();
printf("done.\r\n");
		/*send txt to RPi*/
		UartSend("Done\r\n", 6);
		processTransmit();
	}

	while(1){
		arcUartProcess();

	}

	
	

	return E_SYS;
}

/** @} */