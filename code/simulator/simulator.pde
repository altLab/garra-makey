//
// A Garra Makey (The Makey Claw) - Machine Simulator
//

import processing.serial.*;

Serial serial_port;
MachineState machine_state;
MachineRenderer machine_renderer;

boolean emulate_commands;
long last_update_time;

void setup() {
  size (200, 400);
  
  try {
    serial_port = new Serial(this, "/dev/ttyUSB0", 115200);
    emulate_commands = false;
  } catch (Exception e) {
    println ("Serial port error! Running in command emulation mode");
    emulate_commands = true;
  }
  
  machine_state = new MachineState();
  machine_renderer = new MachineRenderer();

  last_update_time = millis();
  noSmooth();
}

void draw() {
  background(255,213,0);
  long now = millis();
  float delta = (now - last_update_time) / 1000.0;
  last_update_time = now;

  machine_renderer.update (delta, machine_state);
  machine_renderer.draw();
}

void serialEvent(Serial port) { 
  while (port.available() > 0) {
    int command = port.read();
    machine_state.set_from_command (command);
  }
}