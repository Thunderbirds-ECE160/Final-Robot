/*************************************************************************************************************************************************
 * File: IR_Control.h
 * Author: David Purdy, Ported by Alex Westerman
 * Date Created: 10/20/2019
 * Description
 * ======================
 * This class contains the code related to controlling the robot using an IR Remote, as well as 
 *
 * Class Variables
 * ======================
 *
 *
 * Class Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#ifndef IR_CONTROL_H
#define IR_CONTROL_H

#include <Drive.h>
//#include <EIRremote.h>
#include <IRremote.h>

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/
// Some defines for the Remote Buttons (used for easier reading)
#define BTN_POWER 0xFFA25D
#define BTN_FUNC 0xFFE21D
#define BTN_VOLUP 0xFF629D
#define BTN_REWIND 0xFF22DD
#define BTN_PAUSE 0XFF02FD
#define BTN_FSTFWD 0xFFC23D
#define BTN_DOWN 0xFFE01F
#define BTN_VOLDWN 0xFFA857
#define BTN_UP 0xFF906F
#define BTN_EQ 0xFF9867
#define BTN_STREPT 0xFFB04F
#define BTN_0 0xFF6897
#define BTN_1 0xFF30CF
#define BTN_2 0xFF18E7
#define BTN_3 0xFF7A85
#define BTN_4 0xFF10EF
#define BTN_5 0xFF38C7
#define BTN_6 0xFF5AA5
#define BTN_7 0xFF42BD
#define BTN_8 0xFF4AB5
#define BTN_9 0xFF52AD

#define REPEAT 0xFFFFFFFF

#define ELEMENT_WATER 0xB13
#define ELEMENT_GRASS 0xC9A
#define ELEMENT_EARTH 0xEA9
#define ELEMENT_AIR 0xA19
#define ELEMENT_ELECTRICITY 0XE1E
#define ELEMENT_FIRE 0xF19
#define ROBOT_HIT 0x5A5

#define DRIVE_FWD 1
#define DRIVE_BACKWARD 2
#define SPIN_LEFT 3
#define SPIN_RIGHT 4
#define PIV_LEFT 5
#define PIV_RIGHT 6
#define TURN_LEFT 7
#define TURN_RIGHT 8
#define FIRE 9

class IR_Control {
 private:
  Drive* robot;
  IRrecv* remote;
  decode_results prev_cmd;
  decode_results ir_cmd;
  int currentCMD;

  IRsend* transmitter;

 public:
  IR_Control(IRrecv* remote_obj, Drive* robot_obj, IRsend* trans_obj) {
    remote = remote_obj;
    robot = robot_obj;
    transmitter = trans_obj;
  }

  ~IR_Control() {}
  void init();

  void translateIR();
  void elemental();

  void getCMD();
  void parseCMD(int);
  void execCMD();
  void irSendFire();
};
#endif