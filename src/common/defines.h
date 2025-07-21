#ifndef DEFINES_H
#define DEFINES_H 
#include <Arduino.h>

#define REGISTER_ISR(pin, isr, mode) attachInterrupt(digitalPinToInterrupt(pin), isr, mode)
#define UNREGISTER_ISR(pin)          detachInterrupt(digitalPinToInterrupt(pin))
#define RESET asm volatile ("jmp 0")

#endif