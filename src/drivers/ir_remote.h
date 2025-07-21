#ifndef IR_REMOTE_H 
#define IR_REMOTE_H 
#include <Arduino.h>

/*
Received IR code: 0xBA45FF00
Received IR code: 0xB946FF00
Received IR code: 0xB847FF00
Received IR code: 0xBB44FF00

Received IR code: 0xBF40FF00
Received IR code: 0xBC43FF00
Received IR code: 0xF807FF00

Received IR code: 0xEA15FF00
Received IR code: 0xF609FF00
Received IR code: 0xE619FF00
*/

typedef enum {
    CMD_NONE = 0x00000000,
    CMD_ONE = 0xBA45FF00,
    CMD_TWO = 0xB946FF00,
    CMD_THREE = 0xB847FF00,
    CMD_FOUR = 0xBB44FF00,
    CMD_FIVE = 0xBF40FF00,
    CMD_SIX = 0xBC43FF00,
    CMD_SEVEN = 0xF807FF00,
    CMD_EIGHT = 0xEA15FF00,
    CMD_NINE = 0xF609FF00,
    CMD_ZERO = 0xE619FF00
} ir_command_e;

void ir_remote_init(void);
ir_command_e get_ir_command(void);
//void print_command(ir_command_e cmd);

#endif