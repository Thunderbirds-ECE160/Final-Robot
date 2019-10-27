/*
    by: DavidPurdy Oct, 22 2019

******************************************************************************************/

//#include "drive.h"
#include "SR04.h"

//****************pins to change when the robot is configured later
#define trig 12 //pin sending signal 
#define echo 11 //pin receiving the signal 

SR04 sonar = SR04(echo, trig); //sonar pins 1st recieves then 2nd sends
SR04 sonar2 = SR04(echo, trig); // for sonar 2
int half = 500;
int yeet= 1;
//***************pins changed when robot configured
int sensorL = A4;
int sensorR = A5;
int sensorM = A6;

//**********************************************************************************************

//void setup
void setup() {
  Serial.begin(9600);
}



// void loop ****************************************************************************************

void loop() {
  sonar_test();
  line_test();
  read_sonar();
  line_follow();
}

//***************************************************************************************************


void sonar_test() {
  long soundR = sonar.Distance();
  long soundL = sonar2.Distance();
  read_sonar();

  if ( soundR < 25) {
    //pivot_left(); for such a time 
  }

  else if ( soundL < 25) {
    //pivot_right(); for such a time 
  }
}


void read_sonar() {
  //sonar test
  long soundR = sonar.Distance();
  long soundL = sonar2.Distance();
  Serial.print(soundR);
  Serial.println("cm");
  Serial.print(soundL);
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
  }
  if((analogRead(sensorL) > 850 && analogRead(sensorM) < 600 && analogRead(sensorR)> 850 ) || (analogRead(sensorL) <600 && analogRead(sensorM)<600 && analogRead(sensorR) > 850))
  {break;} // break if left and right sensor are reading black and middle sensor is reading white
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
    // pivot left
    if ((analogRead(sensorL)> 850  && analogRead(sensorM) < 600 && analogRead(sensorR) > 850) || analogRead(sensorL)> 850 && analogRead(sensorM)<600 && analogRead(sensorR) < 600))
    {break:} // break if left and right sensor are reading black and middle sensor is reading white
  }
}
else
{
  // move forward // if no line is detected move forward
}
}
void line_test() {

}
