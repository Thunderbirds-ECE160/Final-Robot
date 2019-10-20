//libraries
#include "EIRremote.h"
#include <Servo.h>


const int leftServoPin = 12;
const int rightServoPin = 13;
int receiver = 3; // Signal Pin of IR receiver to Arduino Digital Pin 3
int cmd = 0;

Servo leftServo;
Servo rightServo;
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

#define RED 5
#define GREEN 6
#define BLUE 9
#define DRIVE_FWD 1
#define DRIVE_BACKWARD 3
#define SPIN_LEFT 2
#define SPIN_RIGHT 4
#define GRAB 5
#define PIVOT_LEFT 6
#define PIVOT_RIGHT 7

void translateIR() // takes action based on IR code received

// describing Remote IR codes

{

  switch (results.value)

  {
    case 0xFFA25D: Serial.println("POWER"); break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE");    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");    break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");    break;
    case 0xFF9867: Serial.println("EQ");    break;
    case 0xFFB04F: Serial.println("ST/REPT");    break;
    case 0xFF6897: Serial.println("0");    break;
    case 0xFF30CF: Serial.println("1");    break;
    case 0xFF18E7: Serial.println("2");    break;
    case 0xFF7A85: Serial.println("3");    break;
    case 0xFF10EF: Serial.println("4");    break;
    case 0xFF38C7: Serial.println("5");    break;
    case 0xFF5AA5: Serial.println("6");    break;
    case 0xFF42BD: Serial.println("7");    break;
    case 0xFF4AB5: Serial.println("8");    break;
    case 0xFF52AD: Serial.println("9");    break;
    case 0xFFFFFFFF: Serial.println(" REPEAT"); break;

    default:
      Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR();
    movement_IR();
    elemental();
    irrecv.resume(); // receive the next value
  }
}/* --(end main loop )-- */



void elemental() {
  switch (results.value) {
    case 0xB13: Serial.println("water"); reset_color(); analogWrite(GREEN, 64); analogWrite(BLUE, 128); break;                                   //water, blue
    case 0xC9A: Serial.println("grass"); reset_color(); analogWrite(GREEN, 255); break;                                                          //grass, green
    case 0xEA9: Serial.println("earth"); reset_color(); analogWrite(RED, 128); analogWrite(GREEN, 20); analogWrite(BLUE, 128);  break;           //earth, purple
    case 0xA19: Serial.println("air"); reset_color(); analogWrite(GREEN, 255); analogWrite(BLUE, 255); analogWrite(RED, 255); break;             //air, white
    case 0xE1E: Serial.println("electricity"); reset_color(); analogWrite(RED, 128); analogWrite(GREEN, 128); break;                             //electricity, yellow
    case 0xF19: Serial.println("fire"); reset_color(); analogWrite(RED, 255); analogWrite(GREEN, 55); break;                                    //fire, orange
    case 0x5A5: Serial.println("hit"); reset_color(); analogWrite(RED, 255); break;                                                              //hit, red
  }
}
void reset_color() {
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
}

void movement_IR() {
  if (results.value == 0xFFC23D) {                //right pivot
    cmd = PIVOT_RIGHT;
  }
  else if (results.value == 0xFF22DD) {           //left pivot
    cmd = PIVOT_LEFT;
  }
  else if (results.value == 0xFF629D) {             //forward motion
    cmd = DRIVE_FWD;
  }
  else if (results.value == 0xFFA857) {             //backward motion
    cmd = DRIVE_BACKWARD;

  }




  switch (cmd) {
    case DRIVE_FWD:
      while (0xFFFFFFFF) {
        leftServo.writeMicroseconds(1700);
        rightServo.writeMicroseconds(1300);
        //ps2Boi.read_gamepad(false, VIBES);
        delay(50);
        
      }
      leftServo.writeMicroseconds(1500);
      rightServo.writeMicroseconds(1500);
      break;

    /* case SPIN_LEFT:
         while (ps2Boi.Button(PSB_PAD_LEFT)) {
           leftServo.writeMicroseconds(1300);
           rightServo.writeMicroseconds(1300);
           ps2Boi.read_gamepad(false, VIBES);
           delay(50);
         }
       leftServo.writeMicroseconds(1500);
       rightServo.writeMicroseconds(1500);
       break;
    */
    case DRIVE_BACKWARD:
      while (0xFFFFFFFF) {
        leftServo.writeMicroseconds(1300);
        rightServo.writeMicroseconds(1700);
        //ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }

      leftServo.writeMicroseconds(1500);
      rightServo.writeMicroseconds(1500);
      break;
    /*
        case SPIN_RIGHT:
            while (ps2Boi.Button(PSB_PAD_RIGHT)) {
              leftServo.writeMicroseconds(1700);
              rightServo.writeMicroseconds(1700);
              ps2Boi.read_gamepad(false, VIBES);
              delay(50);
            }

          leftServo.writeMicroseconds(1500);
          rightServo.writeMicroseconds(1500);
          break;

        case GRAB:
            gripperBoi.write(90);
            delay(1000);
            gripperBoi.write(0);
            break;
    */
    case PIVOT_LEFT:
      while (0xFFFFFFFF) {
        leftServo.writeMicroseconds(1700);
        //ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }
      leftServo.writeMicroseconds(1500);
      break;
    case PIVOT_RIGHT:
      while (0xFFFFFFFF) {
        rightServo.writeMicroseconds(1700);
        //ps2Boi.read_gamepad(false, VIBES);
        delay(50);
      }
      rightServo.writeMicroseconds(1500);
      break;
    default:
      break;
  }
  cmd = 0;
  delay(10);
}
