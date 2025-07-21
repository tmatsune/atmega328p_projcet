#include "assert_handler.h"

void assert_handler(void) 
{
  while(1) {
    digitalWrite(13, !digitalRead(13));
    delay(400);
  }
} 

void assert_handler_2(char *err) 
{ 
  drive_stop();
  while(1) {
    digitalWrite(13, !digitalRead(13));
    delay(400);
    Serial.println(err);
  }
} 
