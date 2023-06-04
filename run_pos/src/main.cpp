
//---------------------------------------------------
// Include the AccelStepper Library
#include <Arduino.h>
#include <AccelStepper.h>
// int tep = 54;
// int dir = 55;
// int ena = 38;
// void setup() {
//   pinMode(ena, OUTPUT);
//   pinMode(tep, OUTPUT);
//   pinMode(dir, OUTPUT);
//   digitalWrite(ena, LOW);
// }
// void loop() {
//    digitalWrite(dir, LOW);
//     for(int x = 0; x< 200; x++){
//       digitalWrite(tep, HIGH);
//       delayMicroseconds(1000);
//       digitalWrite(tep, LOW);
//       delayMicroseconds(1000);
//     }
//     delay(1000);
// }
//-----------------------------------------------
// #include <AccelStepper.h>

// Define the motor interface pins
// #define MOTOR_PIN_STEP 54
// #define MOTOR_PIN_DIR 55
// #define MOTOR_PIN_ENA 38

// // Create a new instance of AccelStepper
// AccelStepper stepper(AccelStepper::DRIVER, MOTOR_PIN_STEP, MOTOR_PIN_DIR);

// void setup() {
//   pinMode(MOTOR_PIN_ENA, OUTPUT);
//   digitalWrite(MOTOR_PIN_ENA, LOW);
  
//   // Set the maximum speed and acceleration
//   stepper.setMaxSpeed(1000.0);
//   stepper.setAcceleration(500.0);
// }

// void loop() {
//   // digitalWrite(MOTOR_PIN_DIR, LOW); // Set the motor direction
  
//   // Run the stepper motor forward
//   stepper.moveTo(200);
//   while (stepper.distanceToGo() != 0) {
//     stepper.run();
//   }
//   delay(1000);
  
//   digitalWrite(MOTOR_PIN_DIR, HIGH); // Reverse the motor direction
  
//   // Run the stepper motor backward
//   stepper.moveTo(0);
//   while (stepper.distanceToGo() != 0) {
//     stepper.run();
//   }
//   delay(1000);
// }

//--------------------------------------------------------------
#define MOTOR_PIN_STEP 54
#define MOTOR_PIN_DIR 55
#define MOTOR_PIN_ENA 38
#define step_Y 60
#define Dir_Y 61
#define ena_Y 56

#define step_Z 46
#define Dir_Z 48
#define ena_Z 62

#define step_X 54
#define Dir_X 55
#define ena_X 38

#define end_X 3
#define end_Y 14
#define end_Z 18
// Create a new instance of AccelStepper
AccelStepper Step_X(AccelStepper::DRIVER, step_X, Dir_X);
AccelStepper Step_Y(AccelStepper::DRIVER, step_Y, Dir_Y, ena_Y);
AccelStepper Step_Z(AccelStepper::DRIVER, step_Z, Dir_Z, ena_Z);
void home_Y(){
  int homeY = 0;
  Step_Y.setMaxSpeed(100);
  Step_Y.setAcceleration(100);
  Step_Y.enableOutputs();

  while (digitalRead(end_Y)  == 1){
    Step_Y.moveTo(homeY);
    homeY++;
    Step_Y.run();
  }
  Step_Y.setCurrentPosition(0);
  homeY = 0;
}
void home_Z(){
  int homeZ = 0;
  Step_Z.setMaxSpeed(100);
  Step_Z.setAcceleration(100);
  Step_Z.enableOutputs();

  while (digitalRead(end_Z)  == 1){
    Step_Z.moveTo(homeZ);
    homeZ--;
    Step_Z.run();
  }
  Step_Z.setCurrentPosition(0);
  homeZ = 0;
}
void home_X(){
  int homeX = 0;
  Step_X.setMaxSpeed(100);
  Step_X.setAcceleration(100);
  Step_X.enableOutputs();

  while (digitalRead(end_X)  == 1){
    Step_X.moveTo(homeX);
    homeX++;
    Step_X.run();
  }
  Step_X.setCurrentPosition(0);
  homeX = 0;
}
void home(){
  home_Y();
  home_Z();
  // home_X();
}
void run (byte Ser, int X, int Y, int Z){

  Step_X.moveTo(X);
  Step_Y.moveTo(Y);
  Step_Z.moveTo(Z);
  while (Step_Y.distanceToGo() != 0 || Step_Z.distanceToGo() != 0 || Step_X.distanceToGo() != 0){
    Step_Y.run();   
    Step_Z.run();
    Step_X.run();
  }
}

void setup() {
  pinMode(ena_Y, OUTPUT);
  digitalWrite(ena_Y, LOW);
  pinMode(ena_X, OUTPUT);
  digitalWrite(ena_X, LOW);
  pinMode(ena_Z, OUTPUT);
  digitalWrite(ena_Z, LOW);
  
  pinMode(end_X, INPUT_PULLUP);
  pinMode(end_Y, INPUT_PULLUP);
  pinMode(end_Z, INPUT_PULLUP);

  // Step_X.setEnablePin(38);
  // Step_X.setPinsInverted(false, false, true);
  Step_Y.setEnablePin(56);
  Step_Y.setPinsInverted(false, false, true);
  Step_Z.setEnablePin(62);
  Step_Z.setPinsInverted(false, false, true);

  home();
  
  // Set the maximum speed and acceleration
  Step_X.setMaxSpeed(200);
  Step_X.setAcceleration(200);
  Step_Y.setMaxSpeed(100);
  Step_Y.setAcceleration(100);
  Step_Z.setMaxSpeed(100);
  Step_Z.setAcceleration(100);
}

void loop() {
    delay(500);
    run(180, -235, -300, 250);
    delay(500);
    run(180, -348, -171, 142);
    delay(500);
    run(0, -348, -294, 228);
    delay(500);
    run(0, -348, -153, 112);
    delay(500);
    
}