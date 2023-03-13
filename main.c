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
	initSolenoidPins();
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
			
			if (sensor_data == 0)
			{
				// Set PB11 high
				GPIOB->BSRR |= GPIO_BSRR_BS11;
			}
			else if( sensor_data == 1)
			{
				// Set PB11 low
			GPIOB->BRR |= GPIO_BRR_BR11;
				// do nothing
			}

   
    }
}
