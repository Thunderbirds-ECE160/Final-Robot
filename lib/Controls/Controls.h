/*************************************************************************************************************************************************
 * File: Controls.h
 * Author: Alex Westerman
 * Date Created: 10/24/2019
 * Description
 * ======================
 * This class will be the replacement for the previous IR_Control and
 *PS2_Control libraries Class Variables
 * ======================
 *
 *
 * Class Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#ifndef CONTROLS_H_
#define CONTROLS_H_
/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <Arduino.h>
#include <Drive.h>
#include <IRremote.h>
#include <PS2X_lib.h>

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/

typedef enum { PS2_CONTROL, IR_CONTROL } Control_Sys;

#define DRIVE_FORWARD 1
#define DRIVE_BACKWARD 2
#define SPIN_LEFT 3
#define SPIN_RIGHT 4
#define PIVOT_LEFT 5
#define PIVOT_RIGHT 6
#define TURN_LEFT 7
#define TURN_RIGHT 8
#define FIRE 9

#define V_I_B_E_S 0

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

class Controls {
 private:
  Drive* robot;
  Control_Sys currentSys;
  PS2X* controller;
  IRrecv* remote;
  decode_results prev_cmd;
  decode_results recv_cmd;
  int currentCMD;
  bool isTurnMode;

 public:
  Controls(Drive* _robot, PS2X* _controller) {
    robot = _robot;
    controller = _controller;
    currentSys = Control_Sys::PS2_CONTROL;
    isTurnMode = false;
  }

  Controls(Drive* _robot, IRrecv* _remote) {
    robot = _robot;
    remote = _remote;
    currentSys = Control_Sys::IR_CONTROL;
  }

  ~Controls() {}
  void init();
  void entry();
  void readPS2();
  void readIR();
  void parseInput(int);
};

#endif