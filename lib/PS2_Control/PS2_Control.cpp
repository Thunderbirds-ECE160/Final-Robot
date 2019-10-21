/*************************************************************************************************************************************************
 * Project:
 * Author: Alex Westerman
 * Date Created:
 * Description
 * ======================
 *
 * 
 * Important Functions
 * ======================
 *
 *
 * Misc Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#include "PS2_Control.h"



void PS2_Control::read_controller(){
  ps2_Gamepad->read_gamepad(false, V_I_B_E_S);

  // put your main code here, to run repeatedly:
  if (ps2_Gamepad->ButtonPressed(PSB_PAD_UP) ||
     /* (int(ps2_Analog(PSS_RY)) < 120 || int(ps2_Gamepad->Analog(PSS_LY)) < 120)*/) {
    currentCMD = DRIVE_FWD;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_PAD_LEFT) || int(ps2_Gamepad->Analog(PSS_LX)) < 120) {
    currentCMD = SPIN_LEFT;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_BLUE)) {
    currentCMD = GRAB;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_PAD_DOWN) ||
      (int(ps2_Gamepad->Analog(PSS_RY)) > 135 || int(ps2_Gamepad->Analog(PSS_LY)) > 135)) {
    currentCMD = DRIVE_BACKWARD;
  }

  if (ps2_Gamepad->ButtonPressed(PSB_PAD_RIGHT) || int(ps2_Gamepad->Analog(PSS_LX)) > 135) {
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
    parseCMD();
}

void PS2_Control::parseCMD(){
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

    case GRAB:
      // removed for now
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