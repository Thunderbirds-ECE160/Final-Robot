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

}

void line_test() {

}
