/*************************************************************************************************************************************************
 * File: PS2_Control.cpp
 * Author: Alex Westerman
 * Date Created: 10/20/2019
 * Description
 * ======================
 * This file implements the class prototype(s) defined in PS2_Control.h
 **************************************************************************************************************************************************/
#include "PS2_Control.h"

#include "cpu_map.h"

void PS2_Control::init() {
  robot->attachServos();
  ps2_Gamepad->config_gamepad(PS2_CLOCK, PS2_COMMAND, PS2_ATTENTION, PS2_DATA,
                              true, true);
  remote->enableIRIn();
}

void PS2_Control::irSendFire() {
  // Using example code from class for now, will change implementation later
  // when needed
  // Send the code 3 times. First one is often received as garbage
  for (int i = 0; i < 3; i++) {
    transmitter->sendSony(0x5A5,
                          12);  // Transmit the code 0x5A5 signal from IR LED
    delay(100);
  }
  // Have to enable recievers afterward (for some reason)
  // Delay is used as a "grace period" for the function to complete
  remote->enableIRIn();
}

void PS2_Control::read_controller() {
  ps2_Gamepad->read_gamepad(false, V_I_B_E_S);

  // put your main code here, to run repeatedly:
  if (ps2_Gamepad->ButtonPressed(PSB_PAD_UP)) {
    currentCMD = DRIVE_FWD;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_PAD_LEFT) ||
      int(ps2_Gamepad->Analog(PSS_LX)) < 120) {
    currentCMD = SPIN_LEFT;
  }
  /*
    if (ps2_Gamepad->ButtonPressed(PSB_BLUE)) {
      currentCMD = GRAB;
    }
  */
  if (ps2_Gamepad->ButtonPressed(PSB_PAD_DOWN)) {
    currentCMD = DRIVE_BACKWARD;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_PAD_RIGHT) ||
      int(ps2_Gamepad->Analog(PSS_LX)) > 135) {
    currentCMD = SPIN_RIGHT;
  }

  if (int(ps2_Gamepad->Analog(PSS_RX) < 120)) {
    currentCMD = PIV_TRN_LEFT;
  }

  if (int(ps2_Gamepad->Analog(PSS_RX)) > 135) {
    currentCMD = PIV_TRN_RIGHT;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_START)) {
    isTurnMode = !isTurnMode;
  }
  if (ps2_Gamepad->ButtonPressed(PSB_R2)) {
    currentCMD = PS2_FIRE;
  }
  parseCMD();
}

void PS2_Control::parseCMD() {
  switch (currentCMD) {
    case DRIVE_FWD:
      while (ps2_Gamepad->Button(PSB_PAD_UP)) {
        robot->drive(FORWARD);
        ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
        delay(50);
      }
      robot->stop();
      break;
    case SPIN_LEFT:
      while (ps2_Gamepad->Button(PSB_PAD_LEFT)) {
        robot->spin(LEFT);
        ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
        delay(50);
      }
      robot->stop();
      break;

    case DRIVE_BACKWARD:
      while (ps2_Gamepad->Button(PSB_PAD_DOWN)) {
        robot->drive(BACKWARD);
        ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
        delay(50);
      }
      robot->stop();
      break;

    case SPIN_RIGHT:
      while (ps2_Gamepad->Button(PSB_PAD_RIGHT)) {
        robot->spin(RIGHT);
        ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
        delay(50);
      }
      robot->stop();
      break;

    case PS2_FIRE:
      irSendFire();
      break;
    case PIV_TRN_LEFT:
      if (isTurnMode) {
        while (int(ps2_Gamepad->Analog(PSS_RX) < 120)) {
          robot->turn(LEFT);
          ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        while (int(ps2_Gamepad->Analog(PSS_RX) < 120)) {
          robot->pivot(LEFT);
          ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      }
      break;
    case PIV_TRN_RIGHT:
      if (isTurnMode) {
        while (int(ps2_Gamepad->Analog(PSS_RX) > 130)) {
          robot->turn(RIGHT);
          ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      } else {
        while (int(ps2_Gamepad->Analog(PSS_RX) > 130)) {
          robot->pivot(RIGHT);
          ps2_Gamepad->read_gamepad(false, V_I_B_E_S);
          delay(50);
        }
        robot->stop();
      }
      break;
    default:
      break;
  }
  currentCMD = 0;
}