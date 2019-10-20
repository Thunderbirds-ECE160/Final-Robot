#include <Arduino.h>
#include <Drive.h>
#include <PS2X_lib.h>
#include <Servo.h>

#define DRIVE_FWD 1
#define DRIVE_BACKWARD 3
#define SPIN_LEFT 2
#define SPIN_RIGHT 4
#define GRAB 5
#define PIV_TRN_LEFT 6
#define PIV_TRN_RIGHT 7

boolean isTurnMode = false;

const int ps2_clk = 7;
const int ps2_dat = 8;
const int ps2_cmd = 9;
const int ps2_atn = 10;
int cmd = 0;
PS2X ps2Boi;

#define VIBES 0

// Servo leftServo;
// Servo rightServo;
// Servo gripperBoi;

const int leftServoPin = 12;
const int rightServoPin = 13;
const int gripperBoiPin = 11;

Drive robot(leftServoPin, rightServoPin, gripperBoiPin);

void setup() {
  // put your setup code here, to run once:
  robot.attachServos();
  delay(1000);
  ps2Boi.config_gamepad(ps2_clk, ps2_cmd, ps2_atn, ps2_dat, true, true);
}

void loop() {
  ps2Boi.read_gamepad(false, VIBES);

  // put your main code here, to run repeatedly:
  if (ps2Boi.ButtonPressed(PSB_PAD_UP) ||
      (int(ps2Boi.Analog(PSS_RY)) < 120 || int(ps2Boi.Analog(PSS_LY)) < 120)) {
    cmd = DRIVE_FWD;
  }

  if (ps2Boi.ButtonPressed(PSB_PAD_LEFT) || int(ps2Boi.Analog(PSS_LX)) < 120) {
    cmd = SPIN_LEFT;
  }

  if (ps2Boi.ButtonPressed(PSB_BLUE)) {
    cmd = GRAB;
  }

  if (ps2Boi.ButtonPressed(PSB_PAD_DOWN) ||
      (int(ps2Boi.Analog(PSS_RY)) > 135 || int(ps2Boi.Analog(PSS_LY)) > 135)) {
    cmd = DRIVE_BACKWARD;
  }

  if (ps2Boi.ButtonPressed(PSB_PAD_RIGHT) || int(ps2Boi.Analog(PSS_LX)) > 135) {
    cmd = SPIN_RIGHT;
  }

  if (int(ps2Boi.Analog(PSS_RX) < 120)) {
    cmd = PIV_TRN_LEFT;
  }

  if (int(ps2Boi.Analog(PSS_RX)) > 135) {
    cmd = PIV_TRN_RIGHT;
  }

  if (ps2Boi.ButtonPressed(PSB_START)) {
    isTurnMode = !isTurnMode;
  }

  switch (cmd) {
    case DRIVE_FWD:
      while (ps2Boi.Button(PSB_PAD_UP)) {
        robot.drive(FORWARD);
        ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }
      robot.stop();
      break;
    case SPIN_LEFT:
      while (ps2Boi.Button(PSB_PAD_LEFT)) {
        robot.spin(LEFT);
        ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }
      robot.stop();
      break;

    case DRIVE_BACKWARD:
      while (ps2Boi.Button(PSB_PAD_DOWN)) {
        robot.drive(BACKWARD);
        ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }
      robot.stop();
      break;

    case SPIN_RIGHT:
      while (ps2Boi.Button(PSB_PAD_RIGHT)) {
        robot.spin(RIGHT);
        ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }
      robot.stop();
      break;

    case GRAB:
      // removed for now
      break;
    case PIV_TRN_LEFT:
      if (isTurnMode) {
        while (int(ps2Boi.Analog(PSS_RX) < 120)) {
          robot.turn(LEFT);
          ps2Boi.read_gamepad(false, VIBES);
          delay(50);
        }
        robot.stop();
      } else {
        while (int(ps2Boi.Analog(PSS_RX) < 120)) {
          robot.pivot(LEFT);
          ps2Boi.read_gamepad(false, VIBES);
          delay(50);
        }
        robot.stop();
      }
      break;
    case PIV_TRN_RIGHT:
      if (isTurnMode) {
        while (int(ps2Boi.Analog(PSS_RX) > 130)) {
          robot.turn(RIGHT);
          ps2Boi.read_gamepad(false, VIBES);
          delay(50);
        }
        robot.stop();
      } else {
        while (int(ps2Boi.Analog(PSS_RX) > 130)) {
          robot.pivot(RIGHT);
          ps2Boi.read_gamepad(false, VIBES);
          delay(50);
        }
        robot.stop();
      }
      break;
    default:
      break;
  }
  cmd = 0;
  delay(10);
}