#include "IRSensor.h"
#include "stm32f10x.h"
void initIRSensorpins(void)
{
	// Enable clock for GPIOA
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN;
	
	// Set PA4 as input with pull-down resistor
    IR_SENSOR_PORT->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    IR_SENSOR_PORT->CRL |= GPIO_CRL_CNF4_0;
}

uint8_t read_IR(void) {
    // Read digital value from PA4
    if (GPIOA->IDR & GPIO_IDR_IDR4) {
        return 1;
    } else {
        return 0;
    }
}

void initSolenoidPins(void)
{
	// Enable GPIOB clock
RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

// Configure PB11 as output with 50 MHz speed
GPIOB->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11); // Clear CNF and MODE bits
GPIOB->CRH |= GPIO_CRH_MODE11_1 | GPIO_CRH_MODE11_0; // Set MODE11 to output mode
	
}
