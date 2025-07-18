#include "mcu_init.h"
#include <Arduino.h>

void mcu_init(void){
    Serial.begin(9600);
    Serial.println("Microcontroller Init");
    sei();
}