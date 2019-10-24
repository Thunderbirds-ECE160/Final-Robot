/*************************************************************************************************************************************************
 * File: Controls.cpp
 * Author: Alex Westerman
 * Date Created: 10/24/2019
 * Description
 * ======================
 * This file implements the class prototype(s) defined in Controls.h
 **************************************************************************************************************************************************/
/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include "Controls.h"

#include <cpu_map.h>

void Controls::init() {
  switch (currentSys) {
    case Control_Sys::PS2_CONTROL:
      controller->config_gamepad(PS2_CLOCK, PS2_COMMAND, PS2_ATTENTION,
                                 PS2_DATA);
      break;
    case Control_Sys::IR_CONTROL:
      remote->enableIRIn();
      break;
    default:
      exit(1);  // Error reached, need to restart arduino
      break;
  }
  robot->attachServos();
}

void Controls::entry() {
  switch (currentSys) {
    case Control_Sys::PS2_CONTROL:
      readPS2();
      break;
    case Control_Sys::IR_CONTROL:
      readIR();
      break;
    default:
      exit(1);
      break;
  }
  parseInput(currentCMD);
}

void Controls::parseInput(int cmd) {
  switch (cmd) {
    case DRIVE_FORWARD:

      break;
    case DRIVE_BACKWARD:
      break;
    case SPIN_LEFT:
      break;
    case SPIN_RIGHT:
      break;
    case PIVOT_LEFT:
      break;
    case PIVOT_RIGHT:
      break;
    case TURN_LEFT:
      break;
    case TURN_RIGHT:
      break;
    case FIRE:
      break;
    default:
      break;
  }
}