#ifndef STATE_COMMON_H
#define STATE_COMMON_H 

typedef enum {
    STATE_WAIT, 
    STATE_SEARCH,
    STATE_ATTACK,
    STATE_RETREAT,
    STATE_MANUAL
} state_e;

typedef enum {
    STATE_EVENT_TIMEOUT,
    STATE_EVENT_LINE, 
    STATE_EVENT_ENEMY,
    STATE_EVENT_FINISHED,
    STATE_EVENT_COMMAND,
    STATE_EVENT_NONE
} state_event_e;

#endif