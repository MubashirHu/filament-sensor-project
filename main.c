#include "util.h"
#include "functions.h"
#include "GPIO.h"
#include "ADC.h"
#include "Interrupt.h"
#include "PWM.h"
#include "UART.h"
#include "IRSensor.h"
#include "stm32f10x.h" 
#include "i2c.h"
#include "i2c_lcd_driver.h"
//#include "lcd.h"
#include "string.h"

	
int main(void)
{
	uint8_t my_lcd_addr = 0x3f;
	//Initializations
	clockInit();
	init_UART1();
	initializeADC();
	initIRSensorpins();
	initSolenoidPins();
	i2c_init();		// Set up the clocks, IO ports, and init I2C2 in standard mode
	lcd_init(my_lcd_addr);		// Send the initialization commands to the i2c LCD
	sysTickInit();

	// infinite loop
    while (1)
    {
			
		//char received = USART1_ReceiveChar(); // blocking
		char received = 'a';
		USART1_SendChar(received);
			
		int adc_value = adc_Read();
			
		float temperature = (float)adc_value/4096.0;
		temperature = temperature * 3300;
		temperature = temperature - 1250 ;
		temperature = temperature / 22.5;
			
		lcd_write_cmd(my_lcd_addr, LCD_LN1);	// Position cursor at beginning of line 1
		stringToLCD(my_lcd_addr, "Temp: ");
		intToLCD(my_lcd_addr, temperature);
		stringToLCD(my_lcd_addr, " Deg C");
			
		// Read digital value from PA4
    uint8_t sensor_data = read_sensor_data();
		
    // Do something with sensor_data...
			
			if (sensor_data == 0 || received == 'a')
			{
				// Set PB11 high
				GPIOB->BSRR |= GPIO_BSRR_BS11;
				lcd_write_cmd(my_lcd_addr, LCD_LN2);	// Position cursor at beginning of line 2
				stringToLCD(my_lcd_addr,"State: Not ready");
				
			}
			else if( sensor_data == 1 || received == 'b')
			{
				// Set PB11 low
				GPIOB->BRR |= GPIO_BRR_BR11;
				lcd_write_cmd(my_lcd_addr, LCD_LN2);	// Position cursor at beginning of line 2
				stringToLCD(my_lcd_addr,"  State: Ready");
			}
			sleep_ms(750);
			
    }
		
		
		
}
