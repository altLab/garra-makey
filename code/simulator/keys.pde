//
// handling of keyboard emulation of controller commands 
//

void keyPressed () {
  if (! emulate_commands) return;
  
  switch (key) {
    case 'w':
      machine_state.set_motor_n (true);
      break;
    case 's':
      machine_state.set_motor_s (true);
      break;
    case 'a':
      machine_state.set_motor_w (true);
      break;
    case 'd':
      machine_state.set_motor_e (true);
      break;
    case 'q':
      machine_state.set_claw (true);
      break;
    case 'e':
      machine_state.set_coin (true);
      break;
    default:
      println ("Warning: unrecognized key press");
  }
}

void keyReleased() {
  if (! emulate_commands) return;
  
  switch (key) {
    case 'w':
      machine_state.set_motor_n (false);
      break;
    case 's':
      machine_state.set_motor_s (false);
      break;
    case 'a':
      machine_state.set_motor_w (false);
      break;
    case 'd':
      machine_state.set_motor_e (false);
      break;
    case 'q':
      machine_state.set_claw (false);
      break;
    case 'e':
      machine_state.set_coin (false);
      break;
    default:
      println ("Warning: unrecognized key released");
  }
}