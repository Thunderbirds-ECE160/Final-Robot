/*************************************************************************************************************************************************
 * File: Weapon_Sys.cpp
 * Author: Alex Westerman
 * Date Created: 10/26/19
 * Description
 * ======================
 * This file implements the class prototype(s) defined in Weapon_Sys.h
 **************************************************************************************************************************************************/

#include "Weapon_Sys.h"

#include <cpu_map.h>

void Weapon_Sys::init() {
  reciever->enableIRIn();
  captElement = Element::NONE;
}

void Weapon_Sys::updateLED() {
  switch (captElement) {
    case Element::AIR:
      analogWrite(LED_GREEN, 255);
      analogWrite(LED_BLUE, 255);
      analogWrite(LED_RED, 255);
      break;
    case Element::EARTH:
      analogWrite(LED_RED, 128);
      analogWrite(LED_GREEN, 20);
      analogWrite(LED_BLUE, 128);
      break;
    case Element::ELECTRICITY:
      analogWrite(LED_RED, 255);
      analogWrite(LED_GREEN, 255);
      break;
    case Element::FIRE:
      analogWrite(LED_RED, 255);
      analogWrite(LED_GREEN, 55);
      break;
    case Element::GRASS:
      analogWrite(LED_GREEN, 255);
      break;
    case Element::WATER:
      analogWrite(LED_GREEN, 64);
      analogWrite(LED_BLUE, 128);
      break;
    case Element::ROBOT_HIT:
      analogWrite(LED_RED, 255);
      break;
    case Element::NONE:
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      break;
  }
}

void Weapon_Sys::sendFireCode() {
    // Using example code from class for now, will change implementation later
  // when needed
  // Send the code 3 times. First one is often received as garbage
  for (int i = 0; i < 3; i++) {
    transmitter->sendSony(captElement, 12);  // Transmit the code 0x5A5 signal from IR LED
    delay(50);
  }
  // Have to enable recievers afterward (for some reason)
  //Delay is used as a "grace period" for the function to complete
  reciever->enableIRIn();
}

void Weapon_Sys::processHit() {
    //Will just update the LED for now
    updateLED();
    delay(2000);
    captElement = Element::NONE;
    updateLED();
}

void Weapon_Sys::standby() {}