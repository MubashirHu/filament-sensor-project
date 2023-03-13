#include "util.h"
#include "functions.h"
#include "GPIO.h"
#include "ADC.h"
#include "Interrupt.h"
#include "PWM.h"
#include "UART.h"
#include "IRSensor.h"
#include "stm32f10x.h" 


int main(void)
{
	//Initializations
	clockInit();
	initializeADC();
	initIRSensorpins();
	sysTickInit();
    
	// infinite loop
    while (1)
    {
		
			/*
    int adc_value = adc_Read();
		
		if(adc_value > 0x000 && adc_value <=0x3FF)
		{
			// drive LCD display
			
		} 
			*/
		
		// Read digital value from PA4
    uint8_t sensor_data = read_sensor_data();
		
    // Do something with sensor_data...

   
    }
}
