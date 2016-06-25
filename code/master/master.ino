//
// A Garra Makey (The Makey Claw) - Master Node Firmware 
//

#include "comm_defs.h"
#include <Wire.h>

//
// Configuration
//

const int LED_PIN = 3;
const int MOTOR_N_PIN = 9;
const int MOTOR_S_PIN = 11;
const int MOTOR_E_PIN = 12;
const int MOTOR_W_PIN = 10;
const int CLAW_PIN = 13;
const int COIN_PIN = 8;

// Serial enabled if GM_DEBUG is false.
const bool GM_DEBUG = false;

//
// State
//

struct {
  bool motor_n;
  bool motor_s;
  bool motor_e;
  bool motor_w;
  bool ready;
  bool claw;
  bool coin;
} state, previous_state;

//
// Setup
//

void setup() {
  state.ready = pin_init (LED_PIN, OUTPUT, LOW);
  state.claw = pin_init (CLAW_PIN, OUTPUT, LOW);
  state.coin = pin_init (COIN_PIN, OUTPUT, LOW);
  state.motor_n = pin_init (MOTOR_N_PIN, OUTPUT, LOW);
  state.motor_s = pin_init (MOTOR_S_PIN, OUTPUT, LOW);
  state.motor_e = pin_init (MOTOR_E_PIN, OUTPUT, LOW);
  state.motor_w = pin_init (MOTOR_W_PIN, OUTPUT, LOW);

  previous_state = state;
  
  Wire.begin (GM_MACHINE_ADDRESS);
  Wire.onReceive (get_command);

 
  if (GM_DEBUG) {
     Serial.begin (115200);
     Serial.println("Machine Idle");
  } else {
  Serial.begin(19200);
  }
}

//
// Main loop
//

void loop() {
  delay (100);
  if (!GM_DEBUG) {
  serial_process_command();
  }
}

void serial_process_command() {
  if (Serial.available()) {
	  byte cmd_buffer = Serial.read();
	  execute_command(cmd_buffer);
	} 

}

void execute_command(byte cmd_buffer) {
    if (!state.ready) {
      if (read_command (cmd_buffer, GM_CMD_READY)) {
	      state.ready = true;
	      update_machine();
      }
      return;
    }

    if (GM_DEBUG) {
      Serial.println ("Machine ready!");
    }

    // Update state from command buffer
    state.motor_n = read_command (cmd_buffer, GM_CMD_MOVE_N);
    if (state.motor_n) state.motor_s = false;
    
    state.motor_s = read_command (cmd_buffer, GM_CMD_MOVE_S);
    if (state.motor_s) state.motor_n = false; 
    
    state.motor_e = read_command (cmd_buffer, GM_CMD_MOVE_E);
    if (state.motor_e) state.motor_w = false;
    
    state.motor_w = read_command (cmd_buffer, GM_CMD_MOVE_W);
    if (state.motor_w) state.motor_e = false;
    
    state.claw = read_command (cmd_buffer, GM_CMD_GRAB);
    state.coin = read_command (cmd_buffer, GM_CMD_COIN);
    
    // execute current state
    update_machine();      
}


void get_command (int num_command) {
  byte cmd_buffer;

  while (Wire.available()) {
    cmd_buffer = Wire.read();
    execute_command(cmd_buffer);
  }
}

//
// Helper functions
//

inline bool read_command (byte command, byte mask) {
  if (GM_DEBUG) {
    if ((command & mask) == mask) {
      Serial.print ("Received command ");
      Serial.println (command);
    }
  }
  return (command & mask) == mask;
}

inline void update_machine() {
  diff_pin_set (LED_PIN, previous_state.ready, state.ready);
  diff_pin_set (COIN_PIN, previous_state.coin, state.coin); 
  diff_pin_set (CLAW_PIN, previous_state.claw, state.claw);
  diff_pin_set (MOTOR_N_PIN, previous_state.motor_n, state.motor_n);
  diff_pin_set (MOTOR_S_PIN, previous_state.motor_s, state.motor_s);
  diff_pin_set (MOTOR_E_PIN, previous_state.motor_e, state.motor_e);
  diff_pin_set (MOTOR_W_PIN, previous_state.motor_w, state.motor_w);

  previous_state = state;
}

// Initialises digital pin number PIN with a requested MODE and
// INITIAL_STATE. Returns boolean mapping of initial state (LOW =
// false, HIGH = true)
inline bool pin_init (int pin, int mode, int initial_state) {
  pinMode (pin, mode);
  digitalWrite (pin, initial_state);
  return (initial_state == LOW)? false : true;
}

// Set pin with number PIN to the boolean mapping corresponding to
// STATE
inline void pin_set (int pin, bool state) {
  if (GM_DEBUG) {
    Serial.print ("Setting pin ");
    Serial.print (pin);
    Serial.print ( " to ");
    Serial.println (state);
  }
  digitalWrite (pin, state ? HIGH : LOW);
}

// Set a pin only if the NEW_STATE differs from the OLD_STATE
inline void diff_pin_set (int pin, bool old_state, bool new_state) {
  if (old_state != new_state) {
    pin_set (pin, new_state);
  }
}
