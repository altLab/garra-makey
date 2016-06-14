class MachineState {

  // command constants
  final int GM_CMD_OFF     = 0x00;
  final int GM_CMD_UNUSED  = 0x01;
  final int GM_CMD_READY   = 0x02;
  final int GM_CMD_COIN    = 0x04;
  final int GM_CMD_GRAB    = 0x08;
  final int GM_CMD_MOVE_W  = 0x10;
  final int GM_CMD_MOVE_E  = 0x20;
  final int GM_CMD_MOVE_S  = 0x40;
  final int GM_CMD_MOVE_N  = 0x80;

  // machine state
  boolean motor_n;
  boolean motor_s;
  boolean motor_e;
  boolean motor_w;
  boolean ready;
  boolean claw;
  boolean coin;

  // constructor
  MachineState() {
    this.motor_n = false;
    this.motor_s = false;
    this.motor_e = false;
    this.motor_w = false;
    this.ready = false;
    this.claw = false;
    this.coin = false;
  }
  
  boolean get_ready() {
    return this.ready;
  }
  
  void set_ready (boolean value) {
    this.ready = value;
  }
  
  boolean get_coin() {
    return this.coin;
  }
  
  void set_coin (boolean value) {
    this.coin = value;
  }
  
  boolean get_claw() {
    return this.claw;
  }
  
  void set_claw (boolean value) {
    this.claw = value;
  }
  
  boolean get_motor_n() {
    return this.motor_n;
  }
  
  void set_motor_n (boolean value) {
    if (value && this.motor_s) {
      this.motor_s = false;
    }
    this.motor_n = value;
  }
  
  boolean get_motor_s() {
    return this.motor_s;
  }  
    
  void set_motor_s (boolean value) {
    if (value && this.motor_n) {
      this.motor_n = false;
    }
    this.motor_s = value;
  }
  
  boolean get_motor_e() {
    return this.motor_e;
  }
  
  void set_motor_e (boolean value) {
    if (value && this.motor_w) {
      this.motor_w = false;
    }
    this.motor_e = value;
  }
  
  boolean get_motor_w() {
    return this.motor_w;
  }
  
  void set_motor_w (boolean value) {
    if (value && this.motor_e) {
      this.motor_e = false;
    }
    this.motor_w = value;
  }
  
  void set_from_command (int command) {
    if (! get_ready()) {
      if (read_command (command, GM_CMD_READY)) {
        set_ready (true);
        return;
      }
    }
    
    set_motor_n (read_command (command, GM_CMD_MOVE_N));
    set_motor_s (read_command (command, GM_CMD_MOVE_S));
    set_motor_e (read_command (command, GM_CMD_MOVE_E));
    set_motor_w (read_command (command, GM_CMD_MOVE_W));
    set_claw (read_command (command, GM_CMD_GRAB));
    set_coin (read_command (command, GM_CMD_COIN));
  }
  
  boolean read_command (int command, int mask) {
    return (command & mask) == mask;
  }
}