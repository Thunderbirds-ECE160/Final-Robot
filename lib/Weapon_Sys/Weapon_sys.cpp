/*************************************************************************************************************************************************
 * File: Weapon_Sys.cpp
 * Author: Alex Westerman, David Purdy
 * Port Author : Alex Westerman
 * Date Created: 10/26/19
 * Description
 * ======================
 * This file implements the class prototype(s) defined in Weapon_Sys.h
 **************************************************************************************************************************************************/

#include <cpu_map.h>

#include "Weapon_Sys.h"


void Weapon_Sys::init() {
  reciever->enableIRIn();
  captElement = Element::NONE;
}

IRrecv* Weapon_Sys::getRecv() { return reciever; }

decode_results* Weapon_Sys::getResults() { return &hitCode; }

void Weapon_Sys::updateLED(int hitVal) {
  switch (hitVal) {
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
      Serial.println("Recieved Hit Code (0x5A5)");
      break;
    case Element::NONE:

      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      break;
  }
  offTime = millis() + 5000;
}

void Weapon_Sys::sendFireCode() {
  // Using example code from class for now, will change implementation later
  // when needed
  // Send the code 3 times. First one is often received as garbage
  for (int i = 0; i < 3; i++) {
    transmitter->sendSony(Element::ROBOT_HIT,
                          12);  // Transmit the code 0x5A5 signal from IR LED
    delay(100);
  }

#ifdef DEBUG_ME
  Serial.println("bangbang");
#endif
  // Have to enable recievers afterward (for some reason)
  // Delay is used as a "grace period" for the function to complete
  delay(10);
  reciever->enableIRIn();
}

void Weapon_Sys::processHit() {
  // Will just update the LED for now
  switch (hitCode.value) {
    case Element::AIR:
      captElement = Element::AIR;
#ifdef DEBUG_ME
      Serial.println("Recieved Air Code (0xA19)");
#endif
      break;
    case Element::EARTH:
      captElement = Element::EARTH;
#ifdef DEBUG_ME
      Serial.println("Recieved Earth Code (0xEA9)");
#endif
      break;
    case Element::ELECTRICITY:
#ifdef DEBUG_ME
      Serial.println("Recieved Electricity Code (0xE1E)");
#endif
      captElement = Element::ELECTRICITY;
      break;
    case Element::FIRE:
#ifdef DEBUG_ME
      Serial.println("Recieved Fire Code (0xF19)");
#endif
      captElement = Element::FIRE;
      break;
    case Element::GRASS:
#ifdef DEBUG_ME
      Serial.println("Recieved Grass Code (0xC9A)");
#endif
      captElement = Element::GRASS;
      break;
    case Element::WATER:
#ifdef DEBUG_ME
      Serial.println("Recieved Water Code (0xB13)");
#endif
      captElement = Element::WATER;
      break;
    case Element::ROBOT_HIT:
      captElement = Element::ROBOT_HIT;
#ifdef DEBUG_ME
      Serial.println("Recieved Hit Code (0x5A5)");
#endif
      break;
    default:
      captElement = Element::NONE;
      break;
  }
  updateLED(hitCode.value);
  if (captElement != Element::NONE) {
    offTime = millis() + 5000;
  }
}

void Weapon_Sys::standby() {
  if (reciever->decode(&hitCode)) {
    processHit();
    reciever->resume();
  }
  if (millis() >= offTime) {
    captElement = Element::NONE;
    updateLED(captElement);
  }
}