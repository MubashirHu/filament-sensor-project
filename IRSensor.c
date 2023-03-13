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

uint8_t read_sensor_data(void) {
    // Read digital value from PA4
    if (GPIOA->IDR & GPIO_IDR_IDR4) {
        return 1;
    } else {
        return 0;
    }
}
