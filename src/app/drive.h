#ifndef DRIVE_H 
#define DRIVE_H 
#include <Arduino.h>
#include "drive.h"

// --------------- DRIVE INTERFACE ----------- //

typedef enum
{
    DRIVE_DIR_FORWARD=0,
    DRIVE_DIR_REVERSE=1,
    DRIVE_DIR_ROTATE_LEFT=2,
    DRIVE_DIR_ROTATE_RIGHT=3,
    DRIVE_DIR_ARCTURN_SHARP_LEFT=4,
    DRIVE_DIR_ARCTURN_SHARP_RIGHT=5,
    DRIVE_DIR_ARCTURN_MID_LEFT=6,
    DRIVE_DIR_ARCTURN_MID_RIGHT=7,
    DRIVE_DIR_ARCTURN_WIDE_LEFT=8,
    DRIVE_DIR_ARCTURN_WIDE_RIGHT=9,
    DRIVE_DIR_NONE=10,
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