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
	uint8_t my_lcd_addr = 0x3f, IR_data_curr_state, IR_data_prev_state;
	float temperature;
	//Initializations
	clockInit();
	init_UART1();
	initializeADC();
	initIRSensorpins();
	initSolenoidPins();
	i2c_init();		// Set up the clocks, IO ports, and init I2C2 in standard mode
	lcd_init(my_lcd_addr);		// Send the initialization commands to the i2c LCD
	tim3GpioSetup();
	sysTickInit();

	// infinite loop
    while (1)
    {
		temperature = readTemp();
		
		lcd_write_cmd(my_lcd_addr, LCD_LN1);	// Position cursor at beginning of line 1
		stringToLCD(my_lcd_addr, "Temp: ");
		intToLCD(my_lcd_addr, temperature); 
		stringToLCD(my_lcd_addr, " Deg C   ");
			
    IR_data_curr_state = read_IR();
		
			if (IR_data_curr_state == 1 && IR_data_curr_state != IR_data_prev_state)
			{
				delay(1800000*5);
				GPIOB->BSRR |= GPIO_BSRR_BS11;
				delay(1800000);
				GPIOB->BRR |= GPIO_BRR_BR11;
				
				lcd_write_cmd(my_lcd_addr, LCD_LN2);	// Position cursor at beginning of line 2
				stringToLCD(my_lcd_addr,"   need PLA...");
				
				IR_data_prev_state = IR_data_curr_state;
				updateDutyCycle(50);
				
				
			}
			else if( IR_data_curr_state == 0 && IR_data_curr_state != IR_data_prev_state)
			{
				// Set PB11 low
				GPIOB->BRR |= GPIO_BRR_BR11;
				lcd_write_cmd(my_lcd_addr, LCD_LN2);	// Position cursor at beginning of line 2
				stringToLCD(my_lcd_addr,"   PLA Ready!  ");
				IR_data_prev_state = IR_data_curr_state;
				updateDutyCycle(0);
			}
			sleep_ms(750);
    }
}

