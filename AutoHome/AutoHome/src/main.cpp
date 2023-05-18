#include <Arduino.h>
#include <AccelStepper.h>
#define end_X 6
#define end_Y 14
#define end_Z 18


// int step_X = 54, Dir_X = 55, ena_X = 38;
int step_X = 3, Dir_X = 4, ena_X = 5;
int step_Y = 60, Dir_Y = 61, ena_Y = 56;
int step_Z = 46, Dir_Z = 48, ena_Z = 62;
AccelStepper Step_X(1, step_X, Dir_X, ena_X);
AccelStepper Step_Y(1, step_Y, Dir_Y, ena_Y);
AccelStepper Step_Z(1, step_Z, Dir_Z, ena_Z);

// void home_YZ(){
//   int homeY = 0, homeZ = 0;
//   Step_Y.setMaxSpeed(100);
//   Step_Y.setAcceleration(100);
//   Step_Z.setMaxSpeed(100);
//   Step_Z.setAcceleration(100);
//   Step_Y.enableOutputs();
//   Step_Z.enableOutputs();

//   while (digitalRead(end_Y)  == 1 and digitalRead(end_Y)  == 1){
//     Step_X.moveTo(homeY);
//     Step_Z.moveTo(homeZ);
//     homeY++;
//     homeZ--;
//     Step_Y.run();
//     Step_Z.run();
//   }
//   while (digitalRead(end_Y)  == 1){
//     Step_Y.moveTo(homeY);
//     homeY++;
//     Step_Y.run();
//   }
//   Step_Y.setCurrentPosition(0);
//   while (digitalRead(end_Z)  == 1){
//     Step_Z.moveTo(homeZ);
//     homeZ--;
//     Step_Z.run();
//   }
//   Step_Z.setCurrentPosition(0);
//   homeY = 0; 
//   homeZ = 0;
// }
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
  Step_X.disableOutputs();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(end_X, INPUT_PULLUP);
  pinMode(end_Y, INPUT_PULLUP);
  pinMode(end_Z, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Step_X.setEnablePin(38);
  Step_X.setPinsInverted(false, false, true);
  Step_Y.setEnablePin(56);
  Step_Y.setPinsInverted(false, false, true);
  Step_Z.setEnablePin(62);
  Step_Z.setPinsInverted(false, false, true);
  // home_YZ();
  // home_Y();
  // home_Z();
  home_X();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
}