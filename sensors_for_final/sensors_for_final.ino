//#include <cpu_map.h>
//#include <Drive.h>
/*
    by: DavidPurdy Oct, 22 2019
Modified by Alex W. and Josh R. 
******************************************************************************************/

#include <SR04.h>
#include <Servo.h>

//****************pins to change when the robot is configured later
#define trig 4  // pin sending signal
#define echo 4  // pin receiving the signal
#define LEFT_SERVO_PIN 12
#define RIGHT_SERVO_PIN 13

#define CW_ROT 1300
#define CCW_ROT 1700
#define STOP_ROT 1500
#define CW_LOW_ROT 1450
#define CCW_LOW_ROT 1550

// Drive robot(LEFT_SERVO_PIN, RIGHT_SERVO_PIN, GRIPPER_SERVO_PIN);

SR04 sonar = SR04(echo, trig);  // sonar pins 1st recieves then 2nd sends
Servo leftServo;
Servo rightServo;

int half = 500;//time in sec
int inches = 0;

// Color Storage
int colBlack = 850;
int colWhite = 650;
// tolerance for color storage
int tolerance = 75;

// Calibration storage
int leftData[5];
int middleData[5];
int rightData[5];

//***************pins changed A1,A2,A3
int sensorL = 16;
int sensorR = 15;
int sensorM = 17;

int lastTurn = 0;

//***************************************************************************************************

void sonar_test() {  // this is the function that makes the robot work based off
  // of the sonar

  inches = read_sonar();

  if (inches < 4) {
    //    robot.pivot(LEFT);
    Serial.println("turning");
  } else {
    //    robot.drive(FORWARD);
    Serial.println("forward");
  }
}

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
  Serial.print(inches);
  Serial.println("in");
  delay(half);
  return val;
}

int doAvg(int data[]) {
  int avg = 0;
  for (int x = 0; x < sizeof(data) / sizeof(data[0]); x++) {
    avg = *(data + x) + avg;
  }
  avg = avg / (sizeof(data) / sizeof(data[0]));
  return avg;
}

//***********************************************************************************************************
void line_follow() {
  // Do some calibration
    // Left and right sensors should return a value for black
    // Middle sensor should return a value for white
    // We will collect 5 sample from each sensor and then average as needed

    // Calibrating the left sensor
    //===============================
    // Collect data
    for (int x = 0; x < 5; x++) {
    leftData[x] = analogRead(sensorL);
    }
    // do the average
    int leftAvg = doAvg(leftData);

    // Calibrating the right sensor
    //===============================
    // Collect data
    for (int x = 0; x < 5; x++) {
    rightData[x] = analogRead(sensorR);
    }
    // do the average
    int rightAvg = doAvg(rightData);

    // Calibrating the middle sensor
    //===============================
    // Collect data
    for (int x = 0; x < 5; x++) {
    middleData[x] = analogRead(sensorM);
    }
    // do the average
    int middleAvg = doAvg(middleData);

    // Set corresponding values
    colBlack = (leftAvg + rightAvg) / 2;
    colWhite = middleAvg;

    int drive = 0;
    // Optimizing conditionals here

    
  if (analogRead(sensorL) > ( colBlack - tolerance) && analogRead(sensorM) < (colWhite + tolerance) && analogRead(sensorR) > (colBlack - tolerance)) {
    leftServo.writeMicroseconds(CCW_ROT);
    rightServo.writeMicroseconds(CW_ROT);
  } else if (analogRead(sensorL) < (colWhite + tolerance) && analogRead(sensorM) > ( colBlack - tolerance) && analogRead(sensorR) > (colBlack - tolerance)) {
    leftServo.writeMicroseconds(CW_ROT);
    rightServo.writeMicroseconds(CW_ROT);
  } else   if (analogRead(sensorL) > ( colBlack - tolerance) && analogRead(sensorM) > ( colBlack - tolerance)  && analogRead(sensorR) < (colWhite + tolerance)) {
    leftServo.writeMicroseconds(CCW_ROT);
    rightServo.writeMicroseconds(CCW_ROT);
  }
  delay(10);
}

//****************************************************************************************************************

void setup() {
  Serial.begin(9600);
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  // robot.attachServos();
}

//
// ******************************************************************************************************************

void loop() {
  // sonar_test();
  inches = read_sonar();

    if (read_sonar() <= 4) {
    leftServo.writeMicroseconds(STOP_ROT);
    rightServo.writeMicroseconds(STOP_ROT);
    delay(1000);
    while (read_sonar() <= 4) {
      rightServo.writeMicroseconds(CW_ROT);
      Serial.println("forward");
      delay(50);
    }

    } else if (read_sonar() > 6) {
    while (read_sonar() > 6) {
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      Serial.println("turning");

      delay(50);
    }
    }

    delay(50);
  
  line_follow();
}

//*****************************************************************************************************************



//this is for testing purposes only; checks if color values are correct
void colorRead(){     
  Serial.print(analogRead(17));
Serial.println("M");
Serial.print(analogRead(16));
Serial.println("L");
Serial.println(analogRead(15));
Serial.println("   ");
delay(1000);
}
