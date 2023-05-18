#include <Arduino.h>
#include <AccelStepper.h>

// int step_X = 54, Dir_X = 55, ena_X = 38;
int step_X = 3, Dir_X = 4, ena_X = 5;
int step_Y = 60, Dir_Y = 61, ena_Y = 56;
int step_Z = 46, Dir_Z = 48, ena_Z = 62;
AccelStepper Step_X(1, step_X, Dir_X, ena_X);
AccelStepper Step_Y(1, step_Y, Dir_Y, ena_Y);
AccelStepper Step_Z(1, step_Z, Dir_Z, ena_Z);

void setup(){
  Step_X.setMaxSpeed(200);
  Step_X.setAcceleration(200);

  Step_X.setEnablePin(38);
  Step_X.setPinsInverted(false, false, true);
  Step_X.enableOutputs();

  Step_Y.setMaxSpeed(200);
  Step_Y.setAcceleration(200);

  Step_Y.setEnablePin(56);
  Step_Y.setPinsInverted(false, false, true);
  Step_Y.enableOutputs();
  
  Step_Z.setMaxSpeed(200);
  Step_Z.setAcceleration(200);

  Step_Z.setEnablePin(62);
  Step_Z.setPinsInverted(false, false, true);
  Step_Z.enableOutputs();
}

void loop(){
  Step_X.setCurrentPosition(0);
  while (Step_X.currentPosition() != -200){
    Step_X.setSpeed(-20);
    Step_X.runSpeed();
  }

  // Step_Y.setCurrentPosition(0);
  // while (Step_Y.currentPosition() != -200){
  //   Step_Y.setSpeed(-20);
  //   Step_Y.runSpeed();
  // }

  // Step_Z.setCurrentPosition(0);
  // while (Step_Z.currentPosition() != -200){
  //   Step_Z.setSpeed(-20);
  //   Step_Z.runSpeed();
  // }
}


// #include <Arduino.h>
// #include <Servo.h>
// #define E_X 3
// #define E_Y 14
// #define E_Z 18

// Servo myservo;

// bool gt_E_X, gt_E_Y, gt_E_Z;

// void setup() {
//   Serial.begin(9600);

//   pinMode(E_X, INPUT_PULLUP);
//   pinMode(E_Y, INPUT_PULLUP);
//   pinMode(E_Z, INPUT_PULLUP);

//   myservo.attach(4);
//   // put your setup code here, to run once:
// }

// void loop() {

//   // myservo.write(180);
//   // delay(500);
//   // myservo.write(0);
//   // delay(500);

//   // gt_E_X = digitalRead(E_X);
//   // gt_E_Y = digitalRead(E_Y);
//   // gt_E_Z = digitalRead(E_Z);

//   // Serial.print("X: "); Serial.print(gt_E_X);
//   // Serial.print(" - Y: "); Serial.print(gt_E_Y);
//   // Serial.print(" - Z: "); Serial.println(gt_E_Z);
  

  

//   // put your main code here, to run repeatedly:
// }