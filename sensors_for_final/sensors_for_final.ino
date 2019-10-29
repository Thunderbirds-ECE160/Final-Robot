//#include <cpu_map.h>
//#include <Drive.h>

/*
    by: DavidPurdy Oct, 22 2019

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

int half = 500;
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

//***************pins changed when robot configured
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

void line_follow() {
  /*// Do some calibration
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
  */
  //If the middle sensor does not read white within tolerance
  /*if (analogRead(sensorM) > (colWhite + tolerance)) {
    // Stop
    leftServo.writeMicroseconds(STOP_ROT);
    rightServo.writeMicroseconds(STOP_ROT);
    delay(50);
    // See which sensor has a value closer to white
    // Check the left sensor first
    if (lastTurn == 0) {
      // Dynamic check
      while (analogRead(sensorM) > colWhite+ tolerance) {
        // pivot left
        rightServo.writeMicroseconds(CW_ROT);
        delay(10);
        lastTurn = 1;
      }

    }
    // otherwise check ther right
    else if (lastTurn == 1) {
      // Dynamic check
      while (analogRead(sensorM) > colWhite + tolerance) {
        // pivot left
        leftServo.writeMicroseconds(CW_ROT);
        delay(10);
        lastTurn = 0;
      }

    }}
    /* // Default condition: pivot left
    else {
      // Dynamic check
      while (analogRead(sensorM) > colWhite + tolerance) {
        // pivot left
        rightServo.writeMicroseconds(CW_ROT);
        delay(10);
      }
    }
    }

    // Check if the middle and the left or right sensor both read white
    // Checking left and middle
    else if (analogRead(sensorM) < (colWhite + tolerance) && analogRead(sensorL) < (colWhite + tolerance)) {
    // Do an initial spin (leftwards) for 50ms (calibrate vals)
    // dynamic check
    while (analogRead(sensorM) > colWhite + tolerance) {
      // spin left
      leftServo.writeMicroseconds(CW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      delay(10);
    }
    }
    // checking middle and right
    else if (analogRead(sensorM) < (colWhite + tolerance) && analogRead(sensorR) < (colWhite + tolerance)) {
    // Do an initial spin (rightwards) for 50ms (calibrate vals)
    // dynamic check
    while (analogRead(sensorM) > colWhite + tolerance) {
      // spin right
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CCW_ROT);
      delay(10);
    }}*/
  if (analogRead(sensorL) > ( colBlack - tolerance) && analogRead(sensorM) < (colWhite + tolerance) && analogRead(sensorR) > (colBlack - tolerance)) {
    leftServo.writeMicroseconds(CCW_ROT);
    rightServo.writeMicroseconds(CW_ROT);
  } else if (analogRead(sensorL) < (colWhite + tolerance) && analogRead(sensorM) > ( colBlack - tolerance) && analogRead(sensorR) > (colBlack - tolerance)) {
    leftServo.writeMicroseconds(CW_ROT);
    rightServo.writeMicroseconds(CW_ROT);
  } else   if (analogRead(sensorL) > ( colBlack-tolerance)&& analogRead(sensorM)> ( colBlack - tolerance)  && analogRead(sensorR) < (colWhite + tolerance)) {
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CCW_ROT);
  }
  delay(10);
    /*
      else {
        // Only middle sensor reads white (expected)

        // drive forward
        leftServo.writeMicroseconds(CCW_ROT);
        rightServo.writeMicroseconds(CW_ROT);
      }
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      // delay before next check
      delay(10);

      /*
          if (analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
              analogRead(sensorR) > 850)  // left and right reading black and middle
                                          // reading white, go forward
          {
            drive = 1
          } else if (analogRead(sensorL) > 850 && analogRead(sensorM) > 850 &&
                     analogRead(sensorR) <
                         600)  // left and middle reading black turn right
          {
            while (true) {
              // pivot right;

              if ((analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                   analogRead(sensorR) > 850) ||
                  (analogRead(sensorL) < 600 && analogRead(sensorM) < 600 &&
                   analogRead(sensorR) > 850)) {
                break;  // break if left and right sensor are reading black and
         middle
                        // sensor is reading white
              }
            }
          } else if (analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                     analogRead(sensorR) < 600)  // if the middle and right sensor
                                                 // read white, pivot right
          {
            while (true) {
              // pivotright;
              if ((analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                       analogRead(sensorR) > 850 ||
                   analogRead(sensorL) < 600 && analogRead(sensorM) > 850 &&
                       analogRead(sensorR) < 650)) {
                break;  // break if left and right sensor reading black and middle
                        // sensor is reading white
              }
            }
          } else if (analogRead(sensorL) < 600 && analogRead(sensorM) > 850 &&
                     analogRead(sensorR) > 850)  // if middle and right sensor are
                                                 // reading black pivot left
          {
            while (true) {
              // pivot left;
              if ((analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                   analogRead(sensorR) > 850) ||
                  (analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                   analogRead(sensorR) < 600)) {
                break;
              }
            }
          } else if (analogRead(sensorL) < 600 && analogRead(sensorM) < 600 &&
                     analogRead(sensorR) >
                         850)  // if the left and middle sensor read white pivot
         left
          {
            while (true) {
              // pivot left;
              if (((analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                    analogRead(sensorR) > 850) ||
                   analogRead(sensorL) > 850 && analogRead(sensorM) < 600 &&
                       analogRead(sensorR) < 600)) {
                {
                  break;  // break if left and right sensor are reading black and
                          // middle sensor is reading white
                }
              }
            }
            // else
            //{
            // move forward // if no line is detected move forward
          }*/
  }

  void line_test() {}

  //**********************************************************************************************

  void setup() {
    Serial.begin(9600);
    leftServo.attach(LEFT_SERVO_PIN);
    rightServo.attach(RIGHT_SERVO_PIN);
    // robot.attachServos();
  }

  // void loop
  // ****************************************************************************************

  void loop() {
    // sonar_test();
    // line_test();

    /*inches = read_sonar();

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
    */
    line_follow();
  }
