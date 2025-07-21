#ifndef LINE_H
#define LINE_H
#include <Arduino.h>

typedef enum {
    LINE_NONE, 
    LINE_FRONT, 
    LINE_BACK,
    LINE_LEFT, 
    LINE_RIGHT, 
    LINE_FRONT_LEFT, 
    LINE_FRONT_RIGHT,
    LINE_BACK_LEFT,
    LINE_BACK_RIGHT,
    LINE_DIAGONAL_LEFT,
    LINE_DIAGONAL_RIGHT
} line_pos_e;

line_pos_e get_line_pos(void);
//void print_line_pos(line_pos_e line_pos);

#endif