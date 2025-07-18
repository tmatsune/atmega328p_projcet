#ifndef ASSERT_HANDLER_H 
#define ASSERT_HANDLER_H 
#include <Arduino.h>

void assert_handler(void);

#define ASSERT(cond)  \
  do {                \
    if(!(cond)) {     \
      assert_handler(); \
    }                 \
  } while(0)   

#endif 