#ifndef DRIVE_H 
#define DRIVE_H 
#include <Arduino.h>
#include "drive.h"

// --------------- DRIVE INTERFACE ----------- //

typedef enum
{
    DRIVE_DIR_FORWARD,
    DRIVE_DIR_REVERSE,
    DRIVE_DIR_ROTATE_LEFT,
    DRIVE_DIR_ROTATE_RIGHT,
    DRIVE_DIR_SHARP_LEFT,
    DRIVE_DIR_SHARP_RIGHT,
    DRIVE_DIR_MID_LEFT,
    DRIVE_DIR_MID_RIGHT,
    DRIVE_DIR_WIDE_LEFT,
    DRIVE_DIR_WIDE_RIGHT,
    DRIVE_DIR_FLIP_LEFT,
    DRIVE_DIR_FLIP_RIGHT,
    DRIVE_DIR_NONE,
} drive_dir_e;

typedef enum
{
    DRIVE_SPEED_SLOW,
    DRIVE_SPEED_MEDIUM,
    DRIVE_SPEED_FAST,
    DRIVE_SPEED_MAX
} drive_speed_e;

void drive_stop(void);
void drive_set(drive_dir_e direction, drive_speed_e speed);

#endif