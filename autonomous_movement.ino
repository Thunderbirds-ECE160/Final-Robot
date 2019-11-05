//By: David Purdy
//*****************************************************************
#include <Servo.h>
#define LEFT_SERVO_PIN 12
#define RIGHT_SERVO_PIN 13
#define CW_ROT 1300
#define CCW_ROT 1700
#define STOP_ROT 1500
#define CW_LOW_ROT 1450
#define CCW_LOW_ROT 1550
#define trig 2  // pin sending signal
#define echo 2  // pin receiving the signal
int half = 500;

Servo leftServo;
Servo rightServo;
Servo gripper;

unsigned long int tOFF = 0;
int d = 20;


//**************************************************************
void setup() {
  Serial.begin(9600);
leftServo.attach(12);
rightServo.attach(13);

}


//**************************************************************
void loop() {
  Serial.println(tOFF);
  if ( millis() > tOFF ) {
    leftServo.writeMicroseconds(CW_ROT);
    rightServo.writeMicroseconds(CCW_ROT);
    delay(500);
    leftServo.writeMicroseconds(STOP_ROT);
    rightServo.writeMicroseconds(STOP_ROT);
   delay(500);
    leftServo.writeMicroseconds(CCW_ROT);
    rightServo.writeMicroseconds(CW_ROT);
   delay(500);
    leftServo.writeMicroseconds(STOP_ROT);
    rightServo.writeMicroseconds(STOP_ROT);
  }
 else{
  
  tOFF = millis() + (20 * 142.18);
  Serial.println(tOFF);
  }
  
}


long driveTime() {
  return d * 142.18;
}

/*
  int read_sonar() {  // Serial.prints the reading for the sonar and converts
  // sonar reading to a long value
  int val = 0;
  pinMode(trig, OUTPUT);  // sends trigger pulse
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);  // Reads echo pulse and converts to inches
  val = pulseIn(echo, HIGH) / 74 / 2;
  Serial.print(val);
  Serial.println("in");
  delay(half);
  return val;
  }
*/
