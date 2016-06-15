//
// A Garra Makey (The Makey Claw) - Control Node Example Firmware
//

#include "comm_defs.h"

//
// Configuration
//

const int BUTTON_N_PIN    = 2;
const int BUTTON_S_PIN    = 3;
const int BUTTON_E_PIN    = 4;
const int BUTTON_W_PIN    = 5;
const int BUTTON_CLAW_PIN = 6;
const int BUTTON_COIN_PIN = 7;

#define COMM_DEBUG

//
// Setup
//

void setup() {
  comm_init();
  pinMode (BUTTON_N_PIN, INPUT);
  pinMode (BUTTON_S_PIN, INPUT);
  pinMode (BUTTON_E_PIN, INPUT);
  pinMode (BUTTON_W_PIN, INPUT);
  pinMode (BUTTON_CLAW_PIN, INPUT);
  pinMode (BUTTON_COIN_PIN, INPUT);

  // send the ready command to initialize machine
  byte state = 0x00;
  set_state_bit (true, GM_CMD_READY, &state);
  comm_send (state);
}

//
// Main loop
//

void loop() {
  byte state = 0x00;

  set_state_from_pin (BUTTON_N_PIN, GM_CMD_MOVE_N, &state);
  set_state_from_pin (BUTTON_S_PIN, GM_CMD_MOVE_S, &state);
  set_state_from_pin (BUTTON_E_PIN, GM_CMD_MOVE_E, &state);
  set_state_from_pin (BUTTON_W_PIN, GM_CMD_MOVE_W, &state);
  set_state_from_pin (BUTTON_CLAW_PIN, GM_CMD_GRAB, &state);
  set_state_from_pin (BUTTON_COIN_PIN, GM_CMD_COIN, &state);

  comm_send (state);
  delay (30);
}


