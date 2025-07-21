#include "drive.h"
#include "drivers/pwm.h"

struct DriveSetting
{
    int16_t left;  // LEFT_MOTOR
    int16_t right; // RIGHT_MOTOR
};

static const struct DriveSetting drive_settings[][4] = {
    [DRIVE_DIR_FORWARD] = {
        [DRIVE_SPEED_SLOW] = {.left = 20, .right = 20},
        [DRIVE_SPEED_MEDIUM] = {.left = 100, .right = 100},
        [DRIVE_SPEED_FAST] = {.left = 150, .right = 150},
        [DRIVE_SPEED_MAX] = {.left = 100, .right = 100},
    },
    [DRIVE_DIR_REVERSE] = {
        [DRIVE_SPEED_SLOW] = {.left = -20, .right = -20},
        [DRIVE_SPEED_MEDIUM] = {.left = -100, .right = -100},
        [DRIVE_SPEED_FAST] = {.left = -150, .right = -150},
        [DRIVE_SPEED_MAX] = {.left = -150, .right = -150},
    },
    [DRIVE_DIR_ROTATE_LEFT] = {
        [DRIVE_SPEED_SLOW] = {.left = -20, .right = 20},
        [DRIVE_SPEED_MEDIUM] = {.left = -100, .right = 100},
        [DRIVE_SPEED_FAST] = {.left = -150, .right = 150},
        [DRIVE_SPEED_MAX] = {.left = -150, .right = 150},
    },
    [DRIVE_DIR_ROTATE_RIGHT] = {
        [DRIVE_SPEED_SLOW] = {.left = 25, .right = -25},
        [DRIVE_SPEED_MEDIUM] = {.left = 100, .right = -100},
        [DRIVE_SPEED_FAST] = {.left = 150, .right = -150},
        [DRIVE_SPEED_MAX] = {.left = 150, .right = -150},
    },
    [DRIVE_DIR_ARCTURN_SHARP_LEFT] = {
        [DRIVE_SPEED_SLOW] = {.left = 0, .right = 50},
        [DRIVE_SPEED_MEDIUM] = {.left = 10, .right = 50},
        [DRIVE_SPEED_FAST] = {.left = 25, .right = 75},
        [DRIVE_SPEED_MAX] = {.left = 50, .right = 150},
    },
    [DRIVE_DIR_ARCTURN_SHARP_RIGHT] = {
        [DRIVE_SPEED_SLOW] = {.left = 50, .right = 0},
        [DRIVE_SPEED_MEDIUM] = {.left = 50, .right = 10},
        [DRIVE_SPEED_FAST] = {.left = 75, .right = 25},
        [DRIVE_SPEED_MAX] = {.left = 150, .right = 50},
    },
    [DRIVE_DIR_ARCTURN_MID_LEFT] = {
        [DRIVE_SPEED_SLOW] = {.left = 15, .right = 30},
        [DRIVE_SPEED_MEDIUM] = {.left = 25, .right = 50},
        [DRIVE_SPEED_FAST] = {.left = 35, .right = 70},
        [DRIVE_SPEED_MAX] = {.left = 75, .right = 150},
    },
    [DRIVE_DIR_ARCTURN_MID_RIGHT] = {
        [DRIVE_SPEED_SLOW] = {.left = 30, .right = 15},
        [DRIVE_SPEED_MEDIUM] = {.left = 50, .right = 25},
        [DRIVE_SPEED_FAST] = {.left = 70, .right = 35},
        [DRIVE_SPEED_MAX] = {.left = 150, .right = 75},
    },
    [DRIVE_DIR_ARCTURN_WIDE_LEFT] = {
        [DRIVE_SPEED_SLOW] = {.left = 20, .right = 25},
        [DRIVE_SPEED_MEDIUM] = {.left = 40, .right = 50},
        [DRIVE_SPEED_FAST] = {.left = 60, .right = 70},
        [DRIVE_SPEED_MAX] = {.left = 120, .right = 150},
    },
    [DRIVE_DIR_ARCTURN_WIDE_RIGHT] = {
        [DRIVE_SPEED_SLOW] = {.left = 25, .right = 20},
        [DRIVE_SPEED_MEDIUM] = {.left = 50, .right = 40},
        [DRIVE_SPEED_FAST] = {.left = 70, .right = 60},
        [DRIVE_SPEED_MAX] = {.left = 150, .right = 120},
    },
};




void drive_stop(void){
    //motor_driver_set_mode(LEFT_MOTOR, STOP);
    //motor_driver_set_mode(RIGHT_MOTOR, STOP);
    stop_motors();
}

void drive_set(drive_dir_e dir, drive_speed_e speed){
    int16_t left_motor_speed = drive_settings[dir][speed].left;
    int16_t right_motor_speed = drive_settings[dir][speed].right;
    motor_driver_mode_e left_mode = left_motor_speed > 0 ? FORWARD : REVERSE;
    motor_driver_mode_e right_mode = right_motor_speed > 0 ? FORWARD : REVERSE;
    if (left_motor_speed < 0)
    {
        left_motor_speed *= -1;
    }
    if (right_motor_speed < 0)
    {
        right_motor_speed *= -1;
    }
    motor_driver_set_pwm(LEFT_MOTOR, 50);
    motor_driver_set_pwm(RIGHT_MOTOR, right_motor_speed);
    motor_driver_set_mode(LEFT_MOTOR, left_mode);
    motor_driver_set_mode(RIGHT_MOTOR, right_mode);
}
