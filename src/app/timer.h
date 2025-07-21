#ifndef TIMER_H 
#define TIMER_H
#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

// Poll based timer 
typedef uint32_t timer_t;

// Starts (or restarts) a timer that will expire after timeout_ms milliseconds.
void timer_start(timer_t *timer, uint32_t timeout_ms);  

// Checks whether the timer has expired (i.e., the timeout has occurred).
bool timer_timeout(const timer_t *timer);

// Manually stop or reset the timer.
void timer_clear(timer_t *timer);

#endif 