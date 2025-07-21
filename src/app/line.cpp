#include "line.h"

#define LINE_THRESHOLD 300

line_pos_e get_line_pos(void)
{
    int front_right_value = analogRead(A0);
    int front_left_value = analogRead(A1);
    int back_right_value = analogRead(A2);
    int back_left_value = analogRead(A3);

    bool front_right = front_right_value < LINE_THRESHOLD;
    bool front_left = front_left_value < LINE_THRESHOLD;
    bool back_right = back_right_value < LINE_THRESHOLD;
    bool back_left = back_left_value < LINE_THRESHOLD;

    if(front_left){
        if(front_right) return LINE_FRONT;
        else if(back_left) return LINE_LEFT;
        else return LINE_FRONT_LEFT;
    } else if(front_right){
        if(back_right)return LINE_RIGHT;
        return LINE_FRONT_RIGHT;
    } else if(back_left){
        if(back_right) return LINE_BACK;
        return LINE_BACK_LEFT;
    }else if(back_right){
        if(back_left) return LINE_BACK;
        return LINE_BACK_RIGHT;
    }
    return LINE_NONE;
}

/*
void print_line_pos(line_pos_e line_pos)
{
    switch(line_pos)
    {
        case LINE_NONE: 
            Serial.println("LINE NONE");
            break;
        case LINE_FRONT: 
            Serial.println("LINE FRONT");
            break;
        case LINE_BACK:
            Serial.println("LINE BACK");
            break;       
        case LINE_LEFT: 
            Serial.println("LINE LEFT");
            break;
        case LINE_RIGHT: 
            Serial.println("LINE RIGHT");
            break;
        case LINE_FRONT_LEFT: 
            Serial.println("LINE FRONT LEFT");
            break;
        case LINE_FRONT_RIGHT:
            Serial.println("LINE FRONT RIGHT");
            break;
        case LINE_BACK_LEFT:
            Serial.println("LINE BACK LEFT");
            break;
        case LINE_BACK_RIGHT:
            Serial.println("LINE BACK RIGHT");
            break;
        default: break;
    }
}
*/