#ifndef COMM_DEFS_H
#define COMM_DEFS_H

//
// A Garra Makey (The Makey Claw) - Communication Protocol Defnitions
//

//
// Command Constants
//

const byte GM_CMD_OFF     = 0x00;
const byte GM_CMD_UNUSED  = 0x01;
const byte GM_CMD_READY   = 0x02;
const byte GM_CMD_COIN    = 0x04;
const byte GM_CMD_GRAB    = 0x08;
const byte GM_CMD_MOVE_W  = 0x10;
const byte GM_CMD_MOVE_E  = 0x20;
const byte GM_CMD_MOVE_S  = 0x40;
const byte GM_CMD_MOVE_N  = 0x80;

// Machine address for i2c communication
const int GM_MACHINE_ADDRESS = 8;

#endif // COMM_DEFS_H
