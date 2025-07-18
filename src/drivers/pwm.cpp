#include "pwm.h"
#include "common/assert_handler.h"

#define LEFT_PWM_PIN 11
#define RIGHT_PWM_PIN 3
// 11 = A 
// 12 & 13

// PINS 12 & 13 for LEFT_MOTOR
#define LEFT_MOTOR_PIN_1 12 // A2
#define LEFT_MOTOR_PIN_2 13 // A1

// PINS 8 & 9 for RIGHT MOTOR
#define RIGHT_MOTOR_PIN_1 8 // B1
#define RIGHT_MOTOR_PIN_2 9 // B2

// ----------------------------------------------PWM----------------------------------------------- //

static int left_duty_cycle_percent = 0;
static int right_duty_cycle_percent = 0;

void stop_motors(void)
{
    left_duty_cycle_percent = 0;
    right_duty_cycle_percent = 0;
}

void pwm_init(void)
{
    pinMode(LEFT_PWM_PIN, OUTPUT);
    pinMode(RIGHT_PWM_PIN, OUTPUT);

    TCCR2A = (1 << WGM21) | (1 << WGM20);       // Fast PWM mode
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1);    // Clear OC2A and OC2B on Compare Match
    TIMSK2 = (1 << TOIE2);                      // enables the Timer2 Overflow Interrupt
    TCCR2B = (1 << CS21);                       // Prescaler = 8 (~7.8kHz PWM on 16MHz clock

    OCR2A = 0;                                  // OC2RA IS TIMER COMPARE MATCH FOR PIN 11(PB3)
    OCR2B = 0;                                  // OC2RB IS TIMER COMPARE MATCH FOR PIN 3(PD3)

    pinMode(RIGHT_MOTOR_PIN_1, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN_2, OUTPUT);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);

    pinMode(LEFT_MOTOR_PIN_1, OUTPUT);
    pinMode(LEFT_MOTOR_PIN_2, OUTPUT);
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
}

ISR(TIMER2_OVF_vect){
    OCR2A = left_duty_cycle_percent;
    OCR2B = right_duty_cycle_percent;
}

void pwm_set_duty_cycle(pwm_e pwm_side, int duty_cycle){
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 255) duty_cycle = 255;
    
    switch (pwm_side)
    {
    case LEFT_PWM:
        left_duty_cycle_percent = duty_cycle;
        break;
    case RIGHT_PWM: 
        right_duty_cycle_percent = duty_cycle;
        break;
    default:
        ASSERT(0);
        break;
    }
}

//------------------------------------------ MOTOR DRIVER --------------------------------------- //

struct Motor {
    volatile uint8_t pin_1;
    volatile uint8_t pin_2;
};

static struct Motor motors[] = {
    [LEFT_MOTOR] = {
        .pin_1 = LEFT_MOTOR_PIN_1,
        .pin_2 = LEFT_MOTOR_PIN_2,
    },
    [RIGHT_MOTOR] = {
        .pin_1 = RIGHT_MOTOR_PIN_1,
        .pin_2 = RIGHT_MOTOR_PIN_2,
    }
};

void motor_driver_set_pwm(motor_driver_e driver, int duty_cycle) { 
    pwm_set_duty_cycle((pwm_e)driver, duty_cycle); 
}
void motor_driver_set_mode(motor_driver_e driver, motor_driver_mode_e mode){
    switch(driver){
        case LEFT_MOTOR:
            switch(mode){
                case FORWARD:
                    digitalWrite(motors[LEFT_MOTOR].pin_1, LOW);
                    digitalWrite(motors[LEFT_MOTOR].pin_2, HIGH);
                    break;
                case REVERSE:
                    digitalWrite(motors[LEFT_MOTOR].pin_1, HIGH);
                    digitalWrite(motors[LEFT_MOTOR].pin_2, LOW);
                    break;
                case STOP:
                    digitalWrite(motors[LEFT_MOTOR].pin_1, LOW);
                    digitalWrite(motors[LEFT_MOTOR].pin_2, LOW);
                    break;
                default:
                break;
            }
            break;
        case RIGHT_MOTOR:
            switch(mode){
                case FORWARD:
                    digitalWrite(motors[RIGHT_MOTOR].pin_1, LOW);
                    digitalWrite(motors[RIGHT_MOTOR].pin_2, HIGH);
                    break;
                case REVERSE:
                    digitalWrite(motors[RIGHT_MOTOR].pin_1, HIGH);
                    digitalWrite(motors[RIGHT_MOTOR].pin_2, LOW);
                    break;
                case STOP:
                    digitalWrite(motors[RIGHT_MOTOR].pin_1, LOW);
                    digitalWrite(motors[RIGHT_MOTOR].pin_2, LOW);
                    break;
                default:
                break;
            }
            break;
        default:
            ASSERT(0);
            break;
    }
}

//-------------------------------------------------- DRIVE ----------------------------------------------//
