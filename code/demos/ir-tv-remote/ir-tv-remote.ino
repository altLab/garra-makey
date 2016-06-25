#include "IRLib/IRLib.h"
#include "comm_defs.h"

int RECV_PIN = 11;

IRrecv My_Receiver(RECV_PIN);
IRdecode My_Decoder;
IRdecodeHash My_Hash_Decoder;

void setup()                                                                                                                                                           
{
  My_Receiver.enableIRIn(); // Start the receiver
  My_Receiver.blink13(true); // Enable Blinking in pin 13

  // initialize communication with the claw machine
  comm_init();
  byte state = 0x00;
  set_state_bit (true, GM_CMD_READY, &state);
  comm_send (state);
}

void loop() {
  
  // Reset state
  byte state = 0x00;

  // Check for IR commands
  if (My_Receiver.GetResults (&My_Decoder)) {

    //copy the results to the hash decoder and decode them
    My_Hash_Decoder.copyBuf (&My_Decoder);
    My_Hash_Decoder.decode();
    
    switch (My_Hash_Decoder.hash) {

    case 0x64d4ecee:
      // claw
      set_state_bit (true, GM_CMD_GRAB, &state);
      break;

    case 0xb564b440:
      // up
      set_state_bit (true, GM_CMD_MOVE_N, &state);
      break;

    case 0xd5055bb4:
      set_state_bit (true, GM_CMD_MOVE_W, &state);
      break;
    
    case 0x8e623846:
      // down
      set_state_bit (true, GM_CMD_MOVE_S, &state);
      break;
    
    case 0x42505f87:
      set_state_bit (true, GM_CMD_MOVE_E, &state);
      // left 
      break;
    }

    My_Receiver.resume(); 
  }

  comm_send (state);
  delay (30);
}
