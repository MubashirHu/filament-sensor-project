#include "util.h"
#include "functions.h"
#include "GPIO.h"
#include "ADC.h"
#include "Interrupt.h"
#include "PWM.h"
#include "UART.h"
#include "IRSensor.h"
#include "stm32f10x.h" 
#include "lcd.h"
#include "string.h"

	
int main(void)
{
	//Initializations
	clockInit();
	init_UART1();
	led_IO_init();
	initializeADC();
	initIRSensorpins();
	initSolenoidPins();
	initializeLCD();
	sysTickInit();

	
	// infinite loop
    while (1)
    {
			
		char received = USART1_ReceiveChar();
		USART1_SendChar(received);
			
		int adc_value = adc_Read();
			
		float temperature = (float)adc_value/4096.0;
		temperature = temperature * 3300;
		temperature = temperature - 1250 ;
		temperature = temperature / 22.5;
		
		
		stringToLCD("Temp: ");
		intToLCD(temperature);
		stringToLCD(" Deg C");
			
		// Read digital value from PA4
    uint8_t sensor_data = read_sensor_data();
		
    // Do something with sensor_data...
			
			if (sensor_data == 1 && received == 'b')
			{
				// Set PB11 high
				GPIOB->BSRR |= GPIO_BSRR_BS11;
				LED_ON();
				delay(1800000);
				LED_OFF();
				// Set PB11 low
				GPIOB->BRR |= GPIO_BRR_BR11;
				
				commandToLCD(LCD_LN2);
				stringToLCD("State: Not ready");
			}
			else if( sensor_data == 0 )
			{
				// Set PB11 low
				GPIOB->BRR |= GPIO_BRR_BR11;
				LED_OFF();
				commandToLCD(LCD_LN2);
				stringToLCD("State: Ready");
			}
			delay(1800000);
			commandToLCD(LCD_CLR);
	 
    }
}
