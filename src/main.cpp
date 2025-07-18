#include <Arduino.h>
#include <stdbool.h>
#include "drivers/mcu_init.h"
#include "drivers/pins.h"
#include "drivers/pwm.h"
#include "drivers/adc.h"
#include "app/drive.h"
#include <IRremote.h>

constexpr uint8_t IR_RECEIVE_PIN = 2;
// Create an IR receiver instance
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  Serial.println("Microcontroller Init");
  sei();
  //mcu_init();
  //pins_config();
  //pwm_init();
  //adc_init();
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {

    if (IrReceiver.decode()) {
        // Print the received IR code
        Serial.print("Received IR code: 0x");
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        // Resume to listen for the next code
        IrReceiver.resume();
    }

}

