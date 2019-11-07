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
      break;
    default:
      exit(1);  // Error reached, need to restart arduino
      break;
  }
 // robot->attachServos();
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
      currentCMD = TURN_LEFT;
    } else {
      currentCMD = PIVOT_LEFT;
    }
  }

  if (int(controller->Analog(PSS_RX)) > 135) {
    if (isTurnMode) {
      currentCMD = TURN_RIGHT;
    } else {
      currentCMD = PIVOT_RIGHT;
    }
  }

  if (controller->ButtonPressed(PSB_START)) {
    isTurnMode = !isTurnMode;
  }
  if (controller->ButtonPressed(PSB_R2)||controller->ButtonPressed(PSB_SQUARE)) {
    currentCMD = FIRE;
  }
}

void Controls::readIR() {
  int recv_val = 0;
  // The remote will wait for a button press, then it will decode it, change the
  // proper state var, then waits for next execution
  // Waiting for input
  if (remote->decode(&recv_cmd)) {
    // Check if the button was held
    if (recv_cmd.value == REPEAT) {
      // Do checks based on previous input
      recv_val = prev_cmd.value;

    } else {
      // Do checks based on current input, then stash it
      recv_val = recv_cmd.value;
      // Ensuring its Pass by Value, not by Reference
      memmove(&prev_cmd, &recv_cmd, sizeof(recv_cmd));
    }
    // Allow IR reciever to get new codes
    remote->resume();
  }

  // Get the proper command based on input
  switch (recv_val) {
    case BTN_VOLUP:
      currentCMD = DRIVE_FORWARD;
      break;
    case BTN_VOLDWN:
      currentCMD = DRIVE_BACKWARD;
      break;
    case BTN_REWIND:
      currentCMD = SPIN_LEFT;
      break;
    case BTN_FSTFWD:
      currentCMD = SPIN_RIGHT;
      break;
    case BTN_PAUSE:
      currentCMD = FIRE;
      break;
    case BTN_UP:
      currentCMD = PIVOT_RIGHT;
      break;
    case BTN_DOWN:
      currentCMD = PIVOT_LEFT;
      break;
    case BTN_STREPT:
      currentCMD = TURN_RIGHT;
      break;
    case BTN_0:
      currentCMD = TURN_LEFT;
      break;
    default:
      currentCMD = 0;
      break;
  }
}

void Controls::parseInput(int cmd) {
  switch (cmd) {
    case DRIVE_FORWARD:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (controller->Button(PSB_PAD_UP)) {
          robot->drive(FORWARD);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->drive(FORWARD);
        delay(50);
      }
      break;
    case DRIVE_BACKWARD:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (controller->Button(PSB_PAD_DOWN)) {
          robot->drive(BACKWARD);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->drive(BACKWARD);
        delay(50);
      }
      break;
    case SPIN_LEFT:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (controller->Button(PSB_PAD_LEFT)) {
          robot->spin(LEFT);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->spin(LEFT);
        delay(50);
      }
      break;
    case SPIN_RIGHT:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (controller->Button(PSB_PAD_RIGHT)) {
          robot->spin(RIGHT);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->spin(RIGHT);
        delay(50);
      }
      break;
    case PIVOT_LEFT:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (int(controller->Analog(PSS_RX)) < 120) {
          robot->pivot(LEFT);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->pivot(LEFT);
        delay(50);
      }
      break;
    case PIVOT_RIGHT:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (int(controller->Analog(PSS_RX)) > 135) {
          robot->pivot(RIGHT);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->pivot(RIGHT);
        delay(50);
      }
      break;
    case TURN_LEFT:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (int(controller->Analog(PSS_RX)) < 120 && isTurnMode) {
          robot->turn(LEFT);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->turn(LEFT);
        delay(50);
      }
      break;
    case TURN_RIGHT:
      if (currentSys == Control_Sys::PS2_CONTROL) {
        while (int(controller->Analog(PSS_RX)) > 135 && isTurnMode) {
          robot->turn(RIGHT);
          controller->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        robot->turn(RIGHT);
        delay(50);
      }
      break;
    case FIRE:
      irFireboi->sendFireCode();
      break;
    default:
      // This is where we say the robot should not be moving
      robot->stop();
      break;
  }
  currentCMD = 0;
}

void Controls::entry() {
/*  if (irFireboi->getRecv()->decode(irFireboi->getResults())) {
    irFireboi->processHit();
    irFireboi->getRecv()->resume();
  }*/
  irFireboi->standby();
  switch (currentSys) {
    case Control_Sys::PS2_CONTROL:
      readPS2();
      break;
    case Control_Sys::IR_CONTROL:
      readIR();
      irFireboi->standby();
      break;
    default:
      exit(1);
      break;
  }
  parseInput(currentCMD);
}
