#include "timer.h"

#define TIMER_CLEARED (0u)

// millis() gives the current time in milliseconds since the system started.
// timeout_ms is how long you want the timer to run.
// By adding them, you store the future time when the timer should expire.
// This value is stored in the memory location pointed to by timer.
void timer_start(timer_t *timer, uint32_t timeout_ms)
{
    *timer = millis() + timeout_ms;
}

bool timer_timeout(const timer_t *timer)
{
    if (*timer == TIMER_CLEARED) {      // If the timer is 0 (cleared), it hasn't started → return false.
        return false;                   
    }
    return millis() > *timer;           // check if the current time is greater than the stored expire time
}

void timer_clear(timer_t *timer)
{
    *timer = TIMER_CLEARED;             // Sets the timer value to 0 
}