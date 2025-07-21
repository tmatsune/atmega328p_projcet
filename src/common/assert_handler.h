#ifndef ASSERT_HANDLER_H 
#define ASSERT_HANDLER_H 
#include <Arduino.h>
#include <stdbool.h>
#include "app/drive.h"

void assert_handler(void);
void assert_handler_2(char *err);

#define ASSERT(cond)  \
  do {                \
    if(!(cond)) {     \
      assert_handler(); \
    }                 \
  } while(0)   

#define ASSERT2(cond, err)  \
  do {                \
    if(!(cond)) {     \
      assert_handler_2(err); \
    }                 \
  } while(0)   

#endif 