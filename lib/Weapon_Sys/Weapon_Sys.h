/*************************************************************************************************************************************************
 * File: Weapon_Sys.h
 * Author: Alex Westerman
 * Date Created: 10/24/2019
 * Description
 * ======================
 * This class defines how the IR tronsmitter and IR hit recievers interact with
 *the elements and other robots. Class Variables
 * ======================
 *
 *
 * Class Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#ifndef WEAPONS_SYS_H_
#define WEAPONS_SYS_H_
/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <Arduino.h>
#include <IRremote.h>

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/

typedef enum {
  WATER = 0xB13,
  GRASS = 0xC9A,
  EARTH = 0xEA9,
  AIR = 0xA19,
  ELECTRICITY = 0xE1E,
  FIRE = 0xF19,
  ROBOT_HIT = 0x5A5,
  NONE = 0x0
} Element;

class Weapon_Sys {
 private:
  IRrecv* reciever;
  IRsend* transmitter;
  Element captElement;
  decode_results hitCode;
  unsigned long offTime = 0;

 public:
  Weapon_Sys(IRrecv* recv_, IRsend* send_) {
    reciever = recv_;
    transmitter = send_;
  }
  ~Weapon_Sys(){};
  void init();
  IRrecv* getRecv();
  decode_results* getResults();
  void updateLED(int);
  void sendFireCode();
  void processHit();
  void standby();
};
#endif