#ifndef PWM_H
#define PWM_H
#include <Arduino.h>
#include <stdint.h>

/* 
Valid pins on Nano for analogWrite() (PWM): 3, 5, 6, 9, 10, 11
| Pin | Timer2 Output Compare Unit | Register |
| --- | -------------------------- | -------- |
| 3   | OC2B                       | OCR2B    |
| 11  | OC2A                       | OCR2A    |
*/

typedef enum
{
    LEFT_PWM,
    RIGHT_PWM,
} pwm_e;

typedef enum
{
    LEFT_MOTOR,
    RIGHT_MOTOR,
} motor_driver_e;

typedef enum
{
    FORWARD,
    REVERSE,
    STOP,
} motor_driver_mode_e;

// ----------------- PWM LAYER ---------------- //
void pwm_init(void);
void pwm_set_duty_cycle(pwm_e pwm_side, int duty_cycle);
void stop_motors(void);

// --------------- MOTOR DRIVER -------------- //
void motor_driver_set_mode(motor_driver_e driver, motor_driver_mode_e mode);
void motor_driver_set_pwm(motor_driver_e driver, int duty_cycle);

/*
TCCR2A - Timer/Counter Control Register A for Timer2
       - configures how Timer2 behaves


| Arduino Pin | Timer  | Register | PWM Output | AVR Pin |
| ----------- | ------ | -------- | ---------- | ------- |
| **11**      | Timer2 | OCR2A    | OC2A       | PB3     |
| **3**       | Timer2 | OCR2B    | OC2B       | PD3     |
*/

#endif 