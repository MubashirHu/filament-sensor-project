/******************************************************************************/
/* lcd.c: Routines for LCDs with a Hitachi 44780 compatible controller        */
/*																																						*/
/*	Version 1, Jan 2015		Dave Duguid / Trevor Douglas												*/
/*																																						*/
/******************************************************************************/

#include <string.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "util.h"
#include "IOdef.h"

/******************************************************************************/
//PRIVATE functions
void lcdGpioSetup(void);
void lcdSetup(void);

/*
* Name:					LcdGpioSetup
*	Type:					PRIVATE
* Paramaters: 	none
* Returns:			nothing
* Description: 	This function will initialize the gpio associated with the
*               LCD module.
*/
void lcdGpioSetup(void)
	
// Enable the clocks for Ports B and C, Configure all GPIO connections to the LCD as pushpull outputs.

{
  //Bit 4: Port C, Bit 3: Port B
	RCC->APB2ENR |=  RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN ;   
	
	// Set the config and mode bits for Port B bit 0, 1 and 5 so they will
	// be push-pull outputs (up to 50 MHz)
	//GPIOB->CRL |= GPIO_CRL_MODE5 | GPIO_CRL_MODE1 | GPIO_CRL_MODE0 ;
	//GPIOB->CRL &= ~GPIO_CRL_CNF5 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF0 ;

	GPIOB->CRL &= ~GPIO_CRL_CM5 & ~GPIO_CRL_CM1 & ~GPIO_CRL_CM0 ;
	GPIOB->CRL |= GPIO_CRL_CM5_GP | GPIO_CRL_CM1_GP | GPIO_CRL_CM0_GP ;
	
	
	// Set the config and mode bits for Port C bit 0 through 7 so they will
	// be push-pull outputs (up to 50 MHz)
	//GPIOC->CRL |= GPIO_CRL_MODE7 | GPIO_CRL_MODE6 | GPIO_CRL_MODE5 | GPIO_CRL_MODE4 | GPIO_CRL_MODE3 | GPIO_CRL_MODE2 | GPIO_CRL_MODE1 | GPIO_CRL_MODE0 ;
	//GPIOC->CRL &= ~GPIO_CRL_CNF7 & ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF5 & ~GPIO_CRL_CNF4 & ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF2 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF0 ;
	
	
	GPIOC->CRL &= ~GPIO_CRL_CM7 & ~GPIO_CRL_CM6 & ~GPIO_CRL_CM5 & ~GPIO_CRL_CM4 & ~GPIO_CRL_CM3 & ~GPIO_CRL_CM2 & ~GPIO_CRL_CM1 & ~GPIO_CRL_CM0 ;
	GPIOC->CRL |= GPIO_CRL_CM7_GP | GPIO_CRL_CM6_GP | GPIO_CRL_CM5_GP | GPIO_CRL_CM4_GP | GPIO_CRL_CM3_GP | GPIO_CRL_CM2_GP | GPIO_CRL_CM1_GP | GPIO_CRL_CM0_GP ;	
}

/*
* Name:					lcdSetup
*	Type:					PRIVATE
* Paramaters: 	none
* Returns:			nothing
* Description: 	This function will give the LCD commands to initialize.
*/
void lcdSetup(void)	
{
	commandToLCD(LCD_8B2L);
	commandToLCD(LCD_8B2L);
	commandToLCD(LCD_8B2L);
	commandToLCD(LCD_8B2L);
	commandToLCD(0x0C);
	commandToLCD(0x06);
	commandToLCD(0x01);

	delay(80000);
	delay(80000);
	
}

/******************************************************************************/

//PUBLIC functions

/*
* Name:					initializeLCD
* Type:					PUBLIC
* Parameters: 	none
*	Returns:			nothing	
* Description: 	This function initializes all aspects of the LCD module including the GPIO interface
*/
void initializeLCD(void)
{
	lcdGpioSetup();
	lcdSetup();
}

/*
* Name:					commandToLCD
* Type:					PUBLIC
* Parameters: 	a single byte of command information for the LCD controller
*	Returns:			nothing	
* Description: 	This function sends one command byte to the LCD
*/

void commandToLCD(uint8_t data)
{
    GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
//	  GPIOC->ODR = data;	  
		GPIOC->ODR &= 0xFF00;
	  GPIOC->ODR |= data;
		delay(8000);
	  GPIOB->BSRR = LCD_CM_DIS; //RS low, E high
	  delay(80000);
		
}

/*
* Name:					dataToLCD
* Type:					PUBLIC
* Parameters: 	a single byte of display data for the LCD controller
*	Returns:			nothing	
* Description: 	This function sends one data byte to the LCD
*/

void dataToLCD(uint8_t data)
{
	  GPIOB->BSRR = LCD_DM_ENA; //RS low, E high
//	  GPIOC->ODR = data;
		GPIOC->ODR &= 0xFF00;
	  GPIOC->ODR |= data;
		delay(8000);
	  GPIOB->BSRR = LCD_DM_DIS; //RS low, E high
	  delay(80000);
	
}

/*
* Name:					stringToLCD
* Type:					PUBLIC
* Parameters: 	a pointer to a string of data bytes
*	Returns:			nothing	
* Description: 	This function sends all data bytes in the string to the LCD
*/
void stringToLCD(char * message)
{
	int i=0;
	uint16_t messageLength = strlen(message);
	for (i=0; i<messageLength; ++i)
	{
		dataToLCD(*message);
		++message;
	}
}

void field2(void)
{
		commandToLCD(LCD_FLD2);
		dataToLCD(0x20);
		dataToLCD(0x20);
		dataToLCD(0x20);
		dataToLCD(0x20);	
		commandToLCD(LCD_FLD2);

}

void field4(void)
{
		commandToLCD(LCD_FLD4);
		dataToLCD(0x20);
		dataToLCD(0x20);
		dataToLCD(0x20);
		dataToLCD(0x20);	
		commandToLCD(LCD_FLD4);
}