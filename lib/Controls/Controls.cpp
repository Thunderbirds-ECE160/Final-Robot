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

void Controls::readPS2() {
  controller->read_gamepad(false, V_I_B_E_S);

  // put your main code here, to run repeatedly:
  if (controller->ButtonPressed(PSB_PAD_UP)) {
    currentCMD = DRIVE_FORWARD;
  }

  if (controller->ButtonPressed(PSB_PAD_LEFT) ||
      int(controller->Analog(PSS_LX)) < 120) {
    currentCMD = SPIN_LEFT;
  }
  if (controller->ButtonPressed(PSB_PAD_DOWN)) {
    currentCMD = DRIVE_BACKWARD;
  }

  if (controller->ButtonPressed(PSB_PAD_RIGHT) ||
      int(controller->Analog(PSS_LX)) > 135) {
    currentCMD = SPIN_RIGHT;
  }

  if (int(controller->Analog(PSS_RX) < 120)) {
    if (isTurnMode) {
      currentCMD = PIVOT_LEFT;
    } else {
      currentCMD = PIVOT_LEFT;
    }
  }

  if (int(controller->Analog(PSS_RX)) > 135) {
    if (isTurnMode) {
      currentCMD = TURN_RIGHT;
    } else {
      currentCMD = PIVOT_RIGHT;
    }}

    if (controller->ButtonPressed(PSB_START)) {
      isTurnMode = !isTurnMode;
    }
    if (controller->ButtonPressed(PSB_R2)) {
      currentCMD = PS2_FIRE;
    }
  }
}

void Controls::parseInput(int cmd) {
  switch (cmd) {
    case DRIVE_FORWARD:
      robot->drive(FORWARD);
      delay(50);
      robot->stop();
      break;
    case DRIVE_BACKWARD:
      robot->drive(BACKWARD);
      delay(50);
      robot->stop();
      break;
    case SPIN_LEFT:
      robot->spin(LEFT);
      delay(50);
      robot->stop();
      break;
    case SPIN_RIGHT:
      robot->spin(RIGHT);
      delay(50);
      robot->stop();
      break;
    case PIVOT_LEFT:
      robot->turn(LEFT);
      delay(50);
      robot->stop();
      break;
    case PIVOT_RIGHT:
      robot->turn(RIGHT);
      delay(50);
      robot->stop();
      break;
    case TURN_LEFT:
      robot->pivot(LEFT);
      delay(50);
      robot->stop();
      break;
    case TURN_RIGHT:
      robot->pivot(RIGHT);
      delay(50);
      robot->stop();
      break;
    case FIRE:

      break;
    default:

      break;
  }
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
