/******************************************************************************/
/* lcd.h: Functions and Definitions for Hitachi 44780 based LCDs              */
/*																																						*/
/*	Version 1, Jan 2015		Dave Duguid / Trevor Douglas												*/
/*																																						*/
/******************************************************************************/
#include <stdint.h>

//Commands for Hitachi 44780 compatible LCD controllers
#define LCD_8B2L 	0x38 //		; Enable 8 bit data, 2 display lines
#define LCD_DCB		0x0F //		; Enable Display, Cursor, Blink
#define LCD_MCR		0x06 //		; Set Move Cursor Right
#define LCD_CLR		0X01 //		; Home and clear LCD
#define LCD_LN1		0X80	//	;	Set DDRAM to start of line 1
#define LCD_LN2		0XC0 //		; Set DDRAM to start of line 2
#define LCD_FLD2	0X8C //		; Set DDRAM to 13th position on line 1
#define LCD_FLD4	0XCC //		; Set DDRAM to 13th position on line 2

//Control signal manipulation for LCDs on breadboard PB0:ENA PB1:RS 
//#define LCD_CM_ENA	0X0002F001 //
//#define LCD_CM_DIS	0x0003F000 //
//#define LCD_DM_ENA	0x0000F003 //
//#define LCD_DM_DIS	0x0001F002 //

//Control signal manipulation for LCDs on 352/384/387 board PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA	0X00210002 //
#define LCD_CM_DIS	0x00230000 //
#define LCD_DM_ENA	0x00200003 //
#define LCD_DM_DIS	0x00220001 //

// Public Functions

void initializeLCD(void);
void commandToLCD(uint8_t data);
void stringToLCD(char * message);
void intToLCD(int number);
void dataToLCD(uint8_t data);
void field2(void);
void field4(void);
