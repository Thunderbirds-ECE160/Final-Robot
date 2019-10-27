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
    //pivot_left(); for such a time
  }
  else if(sound > 65){
    //drivefwdfast();
  }
  else if(sound < 65){
    //drivefwdslow();
  }
}


void read_sonar() {    //Serial.prints the reading for the sonar and converts sonar reading to a long value 
  long sound = sonar.Distance();
  Serial.print(sound);
  Serial.println("cm");
  delay(half);
}


void line_follow() {

}

void line_test() {

}
