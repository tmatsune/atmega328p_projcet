#include <Arduino.h>
#include <stdbool.h>
#include "drivers/mcu_init.h"
#include "drivers/pwm.h"
#include "app/timer.h"
#include "app/statemachine.h"

StateMachine state_machine;

void setup() {

  mcu_init();
  pwm_init();
  ir_remote_init();
  state_machine.init();
}

void loop() {

  state_machine.run();
  delay(200);
}

/*
  enemy_pos_e enemy = get_enemy_pos();
  ir_command_e cmd = get_ir_command();
  line_pos_e line_pos = get_line_pos();
  if (enemy != ENEMY_POS_NONE) { print_enemy(enemy); }
  if (cmd != CMD_NONE) { print_command(cmd); }
  if(line_pos != LINE_NONE) {print_line_pos(line_pos); }
  delay(200);
*/
