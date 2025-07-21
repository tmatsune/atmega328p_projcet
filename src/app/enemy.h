#ifndef ENEMY_H
#define ENEMY_H 
#include <stdbool.h>
#include <Arduino.h>

#define RANGE_THRESHOLD 500

typedef enum {
    ENEMY_POS_NONE,
    ENEMY_POS_FRONT_LEFT,
    ENEMY_POS_FRONT,
    ENEMY_POS_FRONT_RIGHT,
    ENEMY_POS_LEFT,
    ENEMY_POS_RIGHT,
    ENEMY_POS_FRONT_AND_FRONT_LEFT,
    ENEMY_POS_FRONT_AND_FRONT_RIGHT,
    ENEMY_POS_FRONT_ALL,
    ENEMY_POS_ERROR
} enemy_pos_e;

enemy_pos_e get_enemy_pos(void);
bool enemy_at_left(enemy_pos_e enemy);
bool enemy_at_right(enemy_pos_e enemy);
bool enmey_at_front(enemy_pos_e enemy);
bool enemy_detected(enemy_pos_e enemy);

//void print_enemy(enemy_pos_e enemy);

#endif 