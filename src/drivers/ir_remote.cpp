#include <IRremote.h>
#include "ir_remote.h"
#include "common/ring_buffer.h"
#include "common/defines.h"

constexpr uint8_t IR_RECEIVE_PIN = 2;

// Create an IR receiver instance
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void ir_remote_init(void)
{
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

ir_command_e get_ir_command(void)
{
    if (IrReceiver.decode()) {
        uint32_t raw_code = IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume();
        return (ir_command_e)raw_code;
    }
    return CMD_NONE;
}

/*
void print_command(ir_command_e cmd)
{
    switch(cmd)
    {
        case CMD_NONE: 
            Serial.println("CMD_NONE"); 
            break;
        case CMD_ZERO: 
            Serial.println("CMD_ZERO"); 
            break;
        case CMD_ONE: 
            Serial.println("CMD_ONE"); 
            break;
        case CMD_TWO: 
            Serial.println("CMD_TWO"); 
            break;
        case CMD_THREE: 
            Serial.println("CMD_THREE"); 
            break;
        case CMD_FOUR: 
            Serial.println("CMD_FOUR"); 
            break;
        case CMD_FIVE: 
            Serial.println("CMD_FIVE"); 
            break;
        case CMD_SIX: 
            Serial.println("CMD_SIX"); 
            break;
        case CMD_SEVEN: 
            Serial.println("CMD_SEVEN"); 
            break;
        case CMD_EIGHT: 
            Serial.println("CMD_EIGHT"); 
            break;
        case CMD_NINE: 
            Serial.println("CMD_NINE"); 
            break;
        default:
            Serial.print("UNKNOWN CMD: 0x");
            Serial.println((uint32_t)cmd, HEX);
            break;
    }
}
*/