/*************************************************************************************************************************************************
 * File: cpu_map.h
 * Author: Alex Westerman
 * Date Created: 10/21/19
 * Description
 * ======================
 *  This file contains some pin definitions for the robot.
 * There are no functions or classes associated with this header.
 **************************************************************************************************************************************************/
#ifndef CPU_MAP_H_
#define CPU_MAP_H_
// Defining the Servo Pins
//***DO NOT CHANGE - HARD WIRED ESSENTIALLY*
#define LEFT_SERVO_PIN 12
#define RIGHT_SERVO_PIN 13
#define GRIPPER_SERVO_PIN 11

// PS2 Controller Stuff
#define PS2_CLOCK 10
#define PS2_DATA 8
#define PS2_COMMAND 11
#define PS2_ATTENTION 7

// IR Pins
// TODO Add IR Pins
#define IR_REMOTE_RECV 4
#define IR_REMOTE_TRANS 3

// LED to display Elemental damage
// TODO Add LED Pins
#define LED_RED 9
#define LED_GREEN 6
#define LED_BLUE 5

#define LINE_SEN_L 16
#define LINE_SEN_R 15
#define LINE_SEN_M 17

#define SONAR_ECHO 4
#define SONAR_TRIG 4

#endif