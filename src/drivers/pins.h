#ifndef PINS_H 
#define PINS_H 

#include <Arduino.h>
#define REGISTER_ISR(pin, isr, mode) attachInterrupt(digitalPinToInterrupt(pin), isr, mode)
#define UNREGISTER_ISR(pin)          detachInterrupt(digitalPinToInterrupt(pin))
  // pinMode(2, INPUT_PULLUP);         // Interrupt pin
  // attachInterrupt(digitalPinToInterrupt(INTERRUPT_2), blink, FALLING);

typedef enum {
    INTERRUPT_2=2,
    INTERRUPT_3=3,
    TEST_LED=13,
} pin_e;

typedef enum {
    RISING_EDGE, 
    FALLING_EDGE 
} trigger_e;

void pins_config(void);

//typedef void (*isr_function)(void);
void enable_interrupt(byte pin);
void disable_interrupt(byte pin);

/*

| Pin | Digital I/O | PWM     | Analog In (ADC) | External Interrupt | Special Functions |
| --- | ----------- | ------- | --------------- | ------------------ | ----------------- |
| D0  | Yes         | No      | No              | No                 | RX (Serial)       |
| D1  | Yes         | No      | No              | No                 | TX (Serial)       |
| D2  | Yes         | No      | No              | **Yes (INT0)**     |                   |
| D3  | Yes         | **Yes** | No              | **Yes (INT1)**     |                   |
| D4  | Yes         | No      | No              | No                 |                   |
| D5  | Yes         | **Yes** | No              | No                 |                   |
| D6  | Yes         | **Yes** | No              | No                 |                   |
| D7  | Yes         | No      | No              | No                 |                   |
| D8  | Yes         | No      | No              | No                 |                   |
| D9  | Yes         | **Yes** | No              | No                 |                   |
| D10 | Yes         | **Yes** | No              | No                 | SS (SPI)          |
| D11 | Yes         | **Yes** | No              | No                 | MOSI (SPI)        |
| D12 | Yes         | No      | No              | No                 | MISO (SPI)        |
| D13 | Yes         | No      | No              | No                 | SCK (SPI), LED    |
| A0  | Yes         | No      | **Yes (ADC0)**  | No                 |                   |
| A1  | Yes         | No      | **Yes (ADC1)**  | No                 |                   |
| A2  | Yes         | No      | **Yes (ADC2)**  | No                 |                   |
| A3  | Yes         | No      | **Yes (ADC3)**  | No                 |                   |
| A4  | Yes         | No      | **Yes (ADC4)**  | No                 | SDA (I2C)         |
| A5  | Yes         | No      | **Yes (ADC5)**  | No                 | SCL (I2C)         |
| A6  | Analog Only | No      | **Yes (ADC6)**  | No                 | Input only        |
| A7  | Analog Only | No      | **Yes (ADC7)**  | No                 | Input only        |


*/

#endif

