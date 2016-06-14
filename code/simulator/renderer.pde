class MachineRenderer {

  final float fixed_vel = 0.5;
  
  float u_pos;
  float w_pos;
  float u_vel;
  float w_vel;
  PVector u0;
  PVector w0;
  PVector u_dir;
  PVector w_dir;
  
  boolean ready;
  boolean coin;
  boolean claw;
  
  MachineRenderer() {
    u_pos = 0.0;
    w_pos = 0.0;
    u_vel = 0.0;
    w_vel = 0.0;
    u0 = new PVector (0, 100);
    w0 = new PVector (100, 50);
    u_dir = new PVector (100, -50);
    w_dir = new PVector (100, 50);
  }

  void update (float delta, MachineState state) {
    if (state.get_motor_n()) {
      u_vel = fixed_vel;
    }
    else if (state.get_motor_s()) {
      u_vel = -fixed_vel; 
    }
    else {
      u_vel = 0.0;
    }
    
    if (state.get_motor_w()) {
      w_vel = -fixed_vel;
    }
    else if (state.get_motor_e()) {
      w_vel = fixed_vel; 
    }
    else {
      w_vel = 0.0;
    }
    
    u_pos = constrain (u_pos + (u_vel * delta), 0.0, 1.0);
    w_pos = constrain (w_pos + (w_vel * delta), 0.0, 1.0);
    
    ready = state.get_ready();
    coin = state.get_coin();
    claw = state.get_claw();
  }
  
  void draw() {
    stroke(0);
    strokeWeight(5);
    fill(255);
    
    quad (100, 200, 100, 50, 0, 100, 0, 250);
    quad (100, 200, 100, 50, 200, 100, 200, 250);

    noFill();

    quad (100, 200, 0, 250, 100, 300, 200, 250);
    
    PVector u = PVector.add (u0, PVector.mult (u_dir, u_pos));
    PVector u_proj = PVector.add (u, w_dir);
    strokeWeight (3);
    line (u.x, u.y, u_proj.x, u_proj.y);

    strokeWeight (10);
    PVector w = PVector.add (u, PVector.mult (w_dir, w_pos));
    point (w.x, w.y);
  }
}