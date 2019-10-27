/*
    by: DavidPurdy Oct, 22 2019

******************************************************************************************/

//#include "drive.h"
#include "SR04.h"
#include <Servo.h> 

//****************pins to change when the robot is configured later
#define trig 5 //pin sending signal 
#define echo 6 //pin receiving the signal 
#define LEFT_SERVO_PIN 12 
#define RIGHT_SERVO_PIN 13

#define CW_ROT 1300
#define CCW_ROT 1700
#define STOP_ROT 1500
#define CW_LOW_ROT 1450
#define CCW_LOW_ROT 1550

SR04 sonar = SR04(echo, trig); //sonar pins 1st recieves then 2nd sends
Servo leftServo;
Servo rightServo;

int half = 500;

//***************pins changed when robot configured
int sensorL = A4;
int sensorR = A5;
int sensorM = A6;

//**********************************************************************************************

void setup() {
  Serial.begin(9600);
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
}



// void loop ****************************************************************************************

void loop() {
  sonar_test();
  //line_test();
  //read_sonar();
  line_follow();
}

//***************************************************************************************************


void sonar_test() {  //this is the function that makes the robot work based off of the sonar 
  long sound = sonar.Distance();

  read_sonar();

  if (sound < 25) {
    void STOP();
    void PIVOT();
  }
  else if(sound > 25){
    void DRIVE();
  }
 
}


void read_sonar() {    //Serial.prints the reading for the sonar and converts sonar reading to a long value 
  long sound = sonar.Distance();
  Serial.print(sound);
  Serial.println("cm");
  delay(half);
}


void line_follow() {
if(analogRead(sensorL)>850 && analogRead (sensorM)<600 && analogRead(sensorR) > 850)// left and right reading black and middle reading white, go forward
{
  // drive forward
}
else if (analogRead(sensorL)>850 && analogRead(sensorM)>850 && analogRead(sensorR)< 600) // left and middle reading black turn right
{
  while(true)
  {
    //pivot right; 
  
  if((analogRead(sensorL) > 850 && analogRead(sensorM) < 600 && analogRead(sensorR)> 850 ) || (analogRead(sensorL) <600 && analogRead(sensorM)<600 && analogRead(sensorR) > 850))
  {break;} // break if left and right sensor are reading black and middle sensor is reading white
}
}
else if (analogRead(sensorL) >850 && analogRead(sensorM)<600 && analogRead(sensorR)<600) // if the middle and right sensor read white, pivot right 
{
  while(true){
    //pivotright;
    if((analogRead(sensorL)> 850 && analogRead(sensorM)< 600 && analogRead(sensorR) > 850 || analogRead(sensorL) < 600 && analogRead(sensorM)> 850 && analogRead(sensorR)< 650 ))
    {break;} // break if left and right sensor reading black and middle sensor is reading white
  }
}
else if (analogRead(sensorL) < 600 && analogRead(sensorM)>850 && analogRead(sensorR)> 850) // if middle and right sensor are reading black pivot left
{
  while(true)
  {
    //pivot left;
    if((analogRead(sensorL) > 850 && analogRead(sensorM)< 600 && analogRead(sensorR)> 850) || (analogRead(sensorL) > 850 && analogRead(sensorM)< 600 && analogRead(sensorR) < 600))
    {break;}
  }
}
else if (analogRead(sensorL)<600 && analogRead(sensorM) < 600 && analogRead(sensorR) > 850) // if the left and middle sensor read white pivot left
{
  while(true)
  {
    // pivot left;
    if (((analogRead(sensorL)> 850  && analogRead(sensorM) < 600 && analogRead(sensorR) > 850) || analogRead(sensorL)> 850 && analogRead(sensorM)<600 && analogRead(sensorR) < 600)){
    {break;} // break if left and right sensor are reading black and middle sensor is reading white
  }
}
//else
//{
  // move forward // if no line is detected move forward
}
}

void line_test() {

}

void PIVOT(){
  leftServo.writeMicroseconds(CCW_ROT);
  delay(50); 
}

void STOP(){
 leftServo.writeMicroseconds(STOP_ROT);
  rightServo.writeMicroseconds(STOP_ROT);
}
