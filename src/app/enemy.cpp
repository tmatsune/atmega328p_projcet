#include "enemy.h"

enemy_pos_e get_enemy_pos(void)
{
    int right_range = analogRead(A4);
    int front_range  = analogRead(A5);
    int left_range = analogRead(A6);
    bool right = right_range > RANGE_THRESHOLD;
    bool front = front_range > RANGE_THRESHOLD;
    bool left = left_range > RANGE_THRESHOLD;
    
    if (front & left & right) {
        return ENEMY_POS_FRONT_ALL;
    } else if (left & right) {
        return ENEMY_POS_ERROR;
    } else if (left) {
        if (front) {
            return ENEMY_POS_FRONT_AND_FRONT_LEFT;
        } else {
            return ENEMY_POS_FRONT_LEFT;
        }
    } else if (right) {
        if (front) {
            return ENEMY_POS_FRONT_AND_FRONT_RIGHT;
        } else {
            return ENEMY_POS_FRONT_RIGHT;
        }
    } else if (front) {
        return ENEMY_POS_FRONT;
    } 
    return ENEMY_POS_NONE;
        
}

bool enemy_at_left(enemy_pos_e enemy)
{
    return enemy == ENEMY_POS_LEFT \
    || enemy == ENEMY_POS_FRONT_LEFT \
    || enemy == ENEMY_POS_FRONT_AND_FRONT_LEFT; 
}

bool enemy_at_right(enemy_pos_e enemy)
{
    return enemy == ENEMY_POS_RIGHT \
    || enemy == ENEMY_POS_FRONT_RIGHT \ 
    || enemy == ENEMY_POS_FRONT_AND_FRONT_RIGHT;
}

bool enemy_at_front(enemy_pos_e enemy)
{
    return enemy == ENEMY_POS_FRONT \
    || enemy == ENEMY_POS_FRONT_ALL;
}

bool enemy_detected(enemy_pos_e enemy) { return enemy != ENEMY_POS_NONE; }

/*
void print_enemy(enemy_pos_e enemy)
{
    switch (enemy)
    {
        case ENEMY_POS_NONE:
            Serial.println("ENEMY NONE");
            break;
        case ENEMY_POS_FRONT_LEFT:
            Serial.println("ENEMY FRONT LEFT");
            break;
        case ENEMY_POS_FRONT:
            Serial.println("ENEMY FRONT");
            break;
        case ENEMY_POS_FRONT_RIGHT:
            Serial.println("ENEMY FRONT RIGHT");
            break;
        case ENEMY_POS_LEFT:
            Serial.println("ENEMY LEFT");
            break;
        case ENEMY_POS_RIGHT:
            Serial.println("ENEMY RIGHT");
            break;
        case ENEMY_POS_FRONT_AND_FRONT_LEFT:
            Serial.println("ENEMY FRONT + FRONT LEFT");
            break;
        case ENEMY_POS_FRONT_AND_FRONT_RIGHT:
            Serial.println("ENEMY FRONT + FRONT RIGHT");
            break;
        case ENEMY_POS_FRONT_ALL:
            Serial.println("ENEMY FRONT ALL");
            break;
        case ENEMY_POS_ERROR:
            Serial.println("ENEMY ERROR");
            break;
        default:
            Serial.println("ENEMY UNKNOWN");
            break;
    }
}
*/