#include "pwm.h"
#include "common/assert_handler.h"

#define LEFT_PWM_PIN 9
#define RIGHT_PWM_PIN 10

#define LEFT_MOTOR_PIN_1 12 // A2
#define LEFT_MOTOR_PIN_2 11 // A1

#define RIGHT_MOTOR_PIN_1 8 // B1
#define RIGHT_MOTOR_PIN_2 7 // B2

static int left_duty_cycle_percent = 0;
static int right_duty_cycle_percent = 0;

void stop_motors(void)
{
    left_duty_cycle_percent = 0;
    right_duty_cycle_percent = 0;

    analogWrite(LEFT_PWM_PIN, 0);
    analogWrite(RIGHT_PWM_PIN, 0);

    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);

    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
}

void pwm_init(void)
{
    pinMode(LEFT_PWM_PIN, OUTPUT);
    pinMode(RIGHT_PWM_PIN, OUTPUT);

    // Set motor control pins
    pinMode(RIGHT_MOTOR_PIN_1, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN_2, OUTPUT);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);

    pinMode(LEFT_MOTOR_PIN_1, OUTPUT);
    pinMode(LEFT_MOTOR_PIN_2, OUTPUT);
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
}

void pwm_set_duty_cycle(pwm_e pwm_side, int duty_cycle)
{
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 255) duty_cycle = 255;

    switch (pwm_side)
    {
    case LEFT_PWM:
        left_duty_cycle_percent = duty_cycle;
        analogWrite(LEFT_PWM_PIN, duty_cycle);
        break;
    case RIGHT_PWM:
        right_duty_cycle_percent = duty_cycle;
        analogWrite(RIGHT_PWM_PIN, duty_cycle);
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
