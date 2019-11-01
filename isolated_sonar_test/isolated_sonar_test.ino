#include <SR04.h>
#include <Servo.h>
#define trig 4
#define echo 4

#define CW_ROT 1300
#define CCW_ROT 1700
#define STOP_ROT 1500


SR04 sonar = SR04(echo, trig);
Servo leftServo;
Servo rightServo;

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
  delay(500);
  return val;
}

void setup() {
  Serial.begin(9600);
  leftServo.attach(12);
  rightServo.attach(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (read_sonar() <= 6) {
    leftServo.writeMicroseconds(STOP_ROT);
    rightServo.writeMicroseconds(STOP_ROT);
    delay(10);
    while (read_sonar() <= 6) {
      rightServo.writeMicroseconds(CW_ROT);
      Serial.println("forward");
      delay(10);
    }

  } else if (read_sonar() > 6) {
    while (read_sonar() > 6) {
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      Serial.println("turning");

      delay(10);
    }
  }
}
