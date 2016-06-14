//
// A Garra Makey (The Makey Claw) - Client Communication Library
//

#include "comm_defs.h"
#include <Wire.h>

// Initialize the library and setup communication
void comm_init () {
  Wire.begin();

#ifdef COMM_DEBUG
    Serial.begin(115200);
#endif
}

// Send a command
void comm_send (byte command) {
  Wire.beginTransmission (GM_MACHINE_ADDRESS);
  Wire.write (command);
  Wire.endTransmission();

#ifdef COMM_DEBUG
    Serial.write (command);
#endif
}

//
// Helper funcions
//

// set a bit on the command state
void set_state_bit (bool value, byte mask, byte *p_state) {
    if (value) { 
      *p_state = *p_state | mask; 
    }
    else {
      *p_state = *p_state & ~(mask);
    }
}

// set a command state bit by reading a pin state
void set_state_from_pin (int pin, byte mask, byte *p_state) {
  if (digitalRead (pin) == HIGH) {
    set_state_bit (true, mask, p_state);
  }
  else {
    set_state_bit (false, mask, p_state);
  }
}
