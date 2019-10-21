/*************************************************************************************************************************************************
 * File: IR_Control.cpp
 * Author: David Purdy, Ported by Alex Westerman
 * Date Created: 10/20/19
 * Description
 * ======================
 * This file implements the class prototype(s) defined in IR_Control.h
 **************************************************************************************************************************************************/

#include "IR_Control.h"

void IR_Control::init() {
  remote->enableIRIn();
  robot->attachServos();
}

void IR_Control::translateIR() {
  switch (ir_cmd.value) {
    case 0xFFA25D:
      Serial.println("POWER");
      break;
    case 0xFFE21D:
      Serial.println("FUNC/STOP");
      break;
    case 0xFF629D:
      Serial.println("VOL+");
      break;
    case 0xFF22DD:
      Serial.println("FAST BACK");
      break;
    case 0xFF02FD:
      Serial.println("PAUSE");
      break;
    case 0xFFC23D:
      Serial.println("FAST FORWARD");
      break;
    case 0xFFE01F:
      Serial.println("DOWN");
      break;
    case 0xFFA857:
      Serial.println("VOL-");
      break;
    case 0xFF906F:
      Serial.println("UP");
      break;
    case 0xFF9867:
      Serial.println("EQ");
      break;
    case 0xFFB04F:
      Serial.println("ST/REPT");
      break;
    case 0xFF6897:
      Serial.println("0");
      break;
    case 0xFF30CF:
      Serial.println("1");
      break;
    case 0xFF18E7:
      Serial.println("2");
      break;
    case 0xFF7A85:
      Serial.println("3");
      break;
    case 0xFF10EF:
      Serial.println("4");
      break;
    case 0xFF38C7:
      Serial.println("5");
      break;
    case 0xFF5AA5:
      Serial.println("6");
      break;
    case 0xFF42BD:
      Serial.println("7");
      break;
    case 0xFF4AB5:
      Serial.println("8");
      break;
    case 0xFF52AD:
      Serial.println("9");
      break;
    case 0xFFFFFFFF:
      Serial.println(" REPEAT");
      break;

    default:
      Serial.println(" other button   ");

  }  // End Case

  delay(500);  // Do not get immediate repeat
}

void IR_Control::elemental() {
  switch (ir_cmd.value) {
    case 0xB13:
      Serial.println("water");
      reset_color();
      analogWrite(LED_GREEN, 64);
      analogWrite(LED_BLUE, 128);
      break;  // water, blue
    case 0xC9A:
      Serial.println("grass");
      reset_color();
      analogWrite(LED_GREEN, 255);
      break;  // grass, green
    case 0xEA9:
      Serial.println("earth");
      reset_color();
      analogWrite(LED_RED, 128);
      analogWrite(LED_GREEN, 20);
      analogWrite(LED_BLUE, 128);
      break;  // earth, purple
    case 0xA19:
      Serial.println("air");
      reset_color();
      analogWrite(LED_GREEN, 255);
      analogWrite(LED_BLUE, 255);
      analogWrite(LED_RED, 255);
      break;  // air, white
    case 0xE1E:
      Serial.println("electricity");
      reset_color();
      analogWrite(LED_RED, 128);
      analogWrite(LED_GREEN, 128);
      break;  // electricity, yellow
    case 0xF19:
      Serial.println("fire");
      reset_color();
      analogWrite(LED_RED, 255);
      analogWrite(LED_GREEN, 55);
      break;  // fire, orange
    case 0x5A5:
      Serial.println("hit");
      reset_color();
      analogWrite(LED_RED, 255);
      break;  // hit, red
  }
}

void reset_color() {
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void IR_Control::getCMD() {
    // The remote will wait for a button press, then it will decode it, change the
  // proper state var, then waits for next execution
  // Waiting for input
  if (remote->decode(&ir_cmd)) {
    // Check if the button was held
    if (ir_cmd.value == REPEAT) {
      // Do checks based on previous input
      parseCMD(prev_cmd.value);
      remote->resume();
    } else {
      // Do checks based on current input, then stash it in case button is held
      parseCMD(ir_cmd.value);
      // Ensuring its Pass by Value, not by Reference
      memmove(&prev_cmd, &ir_cmd, sizeof(ir_cmd));
      remote->resume();
    }
    // Allow IR reciever to get new codes
  } else {
    ir_cmd.value = 0x0;
    parseCMD(ir_cmd.value);
  }
}

void IR_Control::parseCMD(int ir_val){
switch (ir_val){
    case BTN_VOLUP:
        currentCMD = DRIVE_FWD;
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
        currentCMD = PIV_RIGHT;
    break;
    case BTN_DOWN:
        currentCMD = PIV_LEFT;
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