#include <stdint.h>
// Pin definitions
#define IR_SENSOR_PIN 4
#define IR_SENSOR_PORT GPIOA

//function prototypes

void initIRSensorpins(void);

uint8_t read_sensor_data(void);

void initSolenoidPins(void);
