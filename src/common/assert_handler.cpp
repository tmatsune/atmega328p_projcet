#include "assert_handler.h"

void assert_handler(void) 
{
  while(1) {
    digitalWrite(13, !digitalRead(13));
    delay(200);
  }
} 