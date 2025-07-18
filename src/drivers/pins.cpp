#include "pins.h"

void pins_config(void)
{
    // TODO add pin config
}

void enable_interrupt(byte pin) { EIMSK |= (1 << pin); }
void disable_interrupt(byte pin) { EIMSK &= ~(1 << pin); }

