#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <AccelStepper.h>
//------------------Main --------------------------------------------
// int sensorPin = A9;// chân analog kết nối tới cảm biến LM35
// RTC_DS1307 rtc;
// DateTime start_time;
// int voltagePin = A11; // analog input pin to read voltage
// int resetCount;
// void setup() {
//   Serial.begin(9600);
//   while (!Serial) ; // Wait for serial port to connect

//   Wire.begin();
//   rtc.begin();

//   // Set the time when the board is powered on
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   start_time = rtc.now();
//   resetCount = EEPROM.read(0);
//   resetCount++;
//   EEPROM.write(0, resetCount);
// }

// void loop() {
//   DateTime now = rtc.now(); // Get the current time from the RTC module
//   unsigned long elapsed = (now.unixtime() - start_time.unixtime()); // Calculate the elapsed time
//   // Power Supply Status
//   int voltageValue = analogRead(voltagePin); // read voltage value
//   float voltage = voltageValue * (5.0 / 1023.0); // convert voltage value to voltage

//    //đọc giá trị từ cảm biến LM35
//   int reading = analogRead(sensorPin);  
//   //tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biến
//   float voltage_temp = reading * 5.0 / 1024.0; 
//   float temp = voltage_temp * 100.0;

//   resetCount = EEPROM.read(0);
//   // Print the elapsed time in seconds and milliseconds
//   Serial.print(voltage);
//   Serial.print("; ");
//   Serial.print(elapsed);
//   Serial.print("; ");
//   Serial.print(temp);
//   Serial.print("; ");
//   Serial.println(resetCount);


//   delay(1000); // Wait for one second before reading the time again
// }
//--------------Test Robot----------------------------------

#include <TimerOne.h>
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
AccelStepper Step_X(AccelStepper::DRIVER, step_X, Dir_X);
AccelStepper Step_Y(AccelStepper::DRIVER, step_Y, Dir_Y);
AccelStepper Step_Z(AccelStepper::DRIVER, step_Z, Dir_Z);
#define ledPin 4
int ledState = LOW;
int sensorPin = A9;// chân analog kết nối tới cảm biến LM35
RTC_DS1307 rtc;
DateTime now; // Get the current time from the RTC module
DateTime start_time;
int voltagePin = A11; // analog input pin to read voltage
int resetCount;
int tep = 54;
int dir = 55;
int ena = 38;
bool start_job = false;
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

int processSerialData(String serialData) {
  // Split the serial data by semicolon
  int separatorIndex = serialData.indexOf(';');
  if (separatorIndex >= 0) {
    String command = serialData.substring(0, separatorIndex);
    String job = serialData.substring(separatorIndex + 1);
    
    // Print the command and time values
    Serial.print("Command: ");
    Serial.print(command);
    Serial.print(";");
    // Serial.print("Job: ");
    // Serial.print(job);
    // Serial.print(";");
    if (command == "S"){
      start_job = true;
      return 1;
    }
    else if (command == "E"){
      start_job = false;
      return 2;
    }
    else {
      // start_job = false;
      return 3;
    }
      
  }
  return 0;
  // Serial.println(start_job);
  

  // create a DateTime object from the components
}

void blinkLed(){
  int time2start;
  if (Serial.available()) {
    String serialData = Serial.readStringUntil('\n');
    time2start = processSerialData(serialData);
  }
  ledState = !ledState;
  // digitalWrite(LED_BUILTIN, ledState);
  unsigned long elapsed = (now.unixtime()- start_time.unixtime()); // Calculate the elapsed time
  // Power Supply Status
  int voltageValue = analogRead(voltagePin); // read voltage value
  float voltage = voltageValue * (5.0 / 1023.0); // convert voltage value to voltage

   //đọc giá trị từ cảm biến LM35
  int reading = analogRead(sensorPin);  
  //tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biến
  float voltage_temp = reading * 5.0 / 1024.0; 
  float temp = voltage_temp * 100.0;

  resetCount = EEPROM.read(0);
  // Print the elapsed time in seconds and milliseconds
  Serial.print(voltage);
  Serial.print("; ");
  Serial.print(elapsed);
  Serial.print("; ");
  Serial.print(temp);
  Serial.print("; ");
  Serial.println(resetCount);
  

}
void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000); //The led will blink in a half second time interval
  Timer1.attachInterrupt(blinkLed);
  while (!Serial) ; // Wait for serial port to connect


  resetCount = EEPROM.read(0);
  resetCount++;
  EEPROM.write(0, resetCount);
  pinMode(ena, OUTPUT);
  pinMode(tep, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(ena, LOW);
  pinMode(ena_Y, OUTPUT);
  digitalWrite(ena_Y, LOW);  
  pinMode(ena_X, OUTPUT);
  digitalWrite(ena_X, LOW);
  pinMode(ena_Z, OUTPUT);
  digitalWrite(ena_Z, LOW);
  

  Step_X.setMaxSpeed(200);
  Step_X.setAcceleration(200);
  Step_Y.setMaxSpeed(100.0);
  Step_Y.setAcceleration(100.0);
  Step_Z.setMaxSpeed(100.0);
  Step_Z.setAcceleration(100.0);
  Wire.begin();
  rtc.begin();

  // Set the time when the board is powered on
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  start_time = rtc.now();
}

void loop() {
  now = rtc.now();
  if (start_job){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(dir, LOW);
    // for(int x = 0; x< 200; x++){
    //   digitalWrite(tep, HIGH);
    //   delayMicroseconds(1000);
    //   digitalWrite(tep, LOW);
    //   delayMicroseconds(1000);
    // }
    //Z: -50 100  X: -100 -20
    now = rtc.now();
    delay(200);
    if (start_job)run(180, -100, 0, -50);
  now = rtc.now();
    delay(500);
    if (start_job)run(180, -20, 0, 100);
  //   if (start_job)run(180, -348, -171, 142);
  // now = rtc.now();
  //   delay(500);
  //   if (start_job)run(0, -348, -294, 228);
  // now = rtc.now();
  //   delay(500);
  //   if (start_job)run(0, -348, -153, 112);
  // now = rtc.now();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(dir, HIGH);
  }
}



//---------------Timer Interrupt----------------------------

// #include <TimerOne.h>
// #define ledPin 4
// int ledState = LOW;
// int sensorPin = A9;// chân analog kết nối tới cảm biến LM35
// RTC_DS1307 rtc;
// DateTime now; // Get the current time from the RTC module
// DateTime start_time;
// int voltagePin = A11; // analog input pin to read voltage
// int resetCount;
// int tep = 54;
// int dir = 55;
// int ena = 38;
// bool start_job = false;

// void processSerialData(String serialData) {
//   // Split the serial data by semicolon
//   int separatorIndex = serialData.indexOf(';');
//   if (separatorIndex >= 0) {
//     String command = serialData.substring(0, separatorIndex);
//     String job = serialData.substring(separatorIndex + 1);
    
//     // Print the command and time values
//     // Serial.print("Command: ");
//     // Serial.println(command);
//     // Serial.print("Job: ");
//     // Serial.println(job);
//     if (command == "Start"){
//       start_job = true;
//     }
//     else
//       start_job = false;
//   }
//   // Serial.println(start_job);
  

//   // create a DateTime object from the components
// }

// void blinkLed(){
//   if (Serial.available()) {
//     String serialData = Serial.readStringUntil('\n');
//     processSerialData(serialData);
//   }
//   ledState = !ledState;
//   // digitalWrite(LED_BUILTIN, ledState);
//   unsigned long elapsed = (now.unixtime()- start_time.unixtime()); // Calculate the elapsed time
//   // Power Supply Status
//   int voltageValue = analogRead(voltagePin); // read voltage value
//   float voltage = voltageValue * (5.0 / 1023.0); // convert voltage value to voltage

//    //đọc giá trị từ cảm biến LM35
//   int reading = analogRead(sensorPin);  
//   //tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biến
//   float voltage_temp = reading * 5.0 / 1024.0; 
//   float temp = voltage_temp * 100.0;

//   resetCount = EEPROM.read(0);
//   // Print the elapsed time in seconds and milliseconds
//   Serial.print(voltage);
//   Serial.print("; ");
//   Serial.print(elapsed);
//   Serial.print("; ");
//   Serial.print(temp);
//   Serial.print("; ");
//   Serial.println(resetCount);

// }
// void setup() {
//   Serial.begin(9600);
//   Timer1.initialize(1000000); //The led will blink in a half second time interval
//   Timer1.attachInterrupt(blinkLed);
//   while (!Serial) ; // Wait for serial port to connect

//   Wire.begin();
//   rtc.begin();

//   // Set the time when the board is powered on
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   start_time = rtc.now();
//   resetCount = EEPROM.read(0);
//   resetCount++;
//   EEPROM.write(0, resetCount);
//   pinMode(ena, OUTPUT);
//   pinMode(tep, OUTPUT);
//   pinMode(dir, OUTPUT);
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(ena, LOW);
// }

// void loop() {
//   now = rtc.now();
//   if (start_job){
//     digitalWrite(LED_BUILTIN, HIGH);
//     digitalWrite(dir, LOW);
//     for(int x = 0; x< 200; x++){
//       digitalWrite(tep, HIGH);
//       delayMicroseconds(1000);
//       digitalWrite(tep, LOW);
//       delayMicroseconds(1000);
//     }
//     delay(1000);
//   }
//   else {
//     digitalWrite(LED_BUILTIN, LOW);
//     digitalWrite(dir, HIGH);
//   }
// }



//---------Waiting for command-----------------------------
// #define step_Y 46
// #define Dir_Y 48
// #define ena_Y 62
// #define step_Z 46
// #define Dir_Z 48
// #define ena_Z 62
// #define end_X 3
// #define end_Y 14
// #define end_Z 18
// AccelStepper Step_Y(AccelStepper::DRIVER, step_Y, Dir_Y, ena_Y);
// AccelStepper Step_Z(AccelStepper::DRIVER, step_Z, Dir_Z, ena_Z);

// RTC_DS1307 rtc;
// bool Job = false;
// int year, month, day, hour, minute, second;
// DateTime now; // Get the current time from the RTC module
// DateTime start_time;
// void run (byte Ser, int X, int Y, int Z){

//   // Step_X.moveTo(X);
//   Step_Y.moveTo(Y);
//   Step_Z.moveTo(Z);
//   while (Step_Y.distanceToGo() != 0 || Step_Z.distanceToGo() != 0){
//     Step_Y.run();   
//     Step_Z.run();
//   }
// }
// void processSerialData(String serialData) {
//   // Split the serial data by semicolon
//    int separatorIndex = serialData.indexOf(';');
//   if (separatorIndex >= 0) {
//     String command = serialData.substring(0, separatorIndex);
//     // String job = serialData.substring(separatorIndex + 1);
    
//     // Print the command and time values
//     // Serial.print("Command: ");
//     // Serial.println(command);
//     // Serial.print("Job: ");
//     // Serial.println(job);
//     if (command == "Start"){
//       Job = true;
//      start_time = rtc.now();
//     }
//     else
//       Job = false;
//   }
  

//   // create a DateTime object from the components
// }

// void setup() {
//   Serial.begin(9600);  // Initialize serial communication
//   Wire.begin();        // Initialize I2C communication
//   pinMode(LED_BUILTIN, OUTPUT);
//   rtc.begin();
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   Step_Y.setMaxSpeed(100.0);
//   Step_Y.setAcceleration(100.0);
//   Step_Z.setMaxSpeed(100.0);
//   Step_Z.setAcceleration(100.0);
// }
// void loop() {
//   now = rtc.now();
//   if (Serial.available()) {
//     String serialData = Serial.readStringUntil('\n');
//     processSerialData(serialData);   
//   }
//   unsigned long elapsed = (now.unixtime()- start_time.unixtime()); // Calculate the elapsed time
//   Serial.print("Job = "); Serial.print(Job); Serial.print("elapsed = "); Serial.println(elapsed);
//   if (Job == true && elapsed<=60){
//     Serial.println("Start");
//     delay(200);
//     run(180, -235, -300, 250);
//     delay(500);
//     run(180, -348, -171, 142);
//     delay(500);
//     run(0, -348, -294, 228);
//     delay(500);
//     run(0, -348, -153, 112);
//     delay(500);
//     run(0, -450, -153, 112);
//     delay(500);
//     run(180, -480, -300, 216);
//     delay(500);
//     run(180, -216, -147, 101);
//     delay(500);
//     run(0, -56, -289, 229);
//     delay(500);
//     run(0, -259, -164, 122);
//     delay(500);
//     run(180, -259, -295, 234);
//     delay(500);
//   }
//   else{
//     Serial.println("Pause");
//   }
//   delay(1000);
// }

//----------Motor Temp--------------------------------------
// int sensorPin = A9;// chân analog kết nối tới cảm biến LM35
 
// void setup() {
//   Serial.begin(9600);  //Khởi động Serial ở mức baudrate 9600
//   // Bạn không cần phải pinMode cho các chân analog trước khi dùng nó
// }
 
// void loop() {
//  //đọc giá trị từ cảm biến LM35
//  int reading = analogRead(sensorPin);  
 
//  //tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biến
//  float voltage = reading * 5.0 / 1024.0; 
 
//  // ở trên mình đã giới thiệu, cứ mỗi 10mV = 1 độ C.
//  // Vì vậy nếu biến voltage là biến lưu hiệu điện thế (đơn vị Volt)
//  // thì ta chỉ việc nhân voltage cho 100 là ra được nhiệt độ!
 
//  float temp = voltage * 100.0;
 
//  Serial.println(temp);
//  /*Mẹo:
//    Các bạn phaỉ khai báo phần thực cho toàn bộ các số thực nhé!
//  */
//  delay(1000);//đợi 1 giây cho lần đọc tiếp theo
// }

//----------Reset Count--------------------------------------
// int resetCount;
// void setup() {
//   Serial.begin(9600);
//   // increment the reset count and store it in EEPROM
//   resetCount = EEPROM.read(0);
//   resetCount++;
//   // EEPROM.write(0, resetCount);
//   EEPROM.write(0, 254);
// }
// void loop() {
//   // read the reset count from EEPROM
//   resetCount = EEPROM.read(0);
//   Serial.print("Reset count: ");
//   Serial.println(resetCount);
//   delay(1000);
// }

//------------------------Setup for RTC Module---------------------
// RTC_DS1307 rtc;

// char daysOfTheWeek[7][12] = {
//   "Sunday",
//   "Monday",
//   "Tuesday",
//   "Wednesday",
//   "Thursday",
//   "Friday",
//   "Saturday"
// };

// void setup () {
//   Serial.begin(9600);

//   // SETUP RTC MODULE
//   if (! rtc.begin()) {
//     Serial.println("Couldn't find RTC");
//     Serial.flush();
//     while (1);
//   }

//   // automatically sets the RTC to the date & time on PC this sketch was compiled
//   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   rtc.adjust(DateTime(F(__DATE__), F("16:58:00")));   
//   // manually sets the RTC with an explicit date & time, for example to set
//   // January 21, 2021 at 3am you would call:
//   // rtc.adjust(DateTime(2023, 3, 5, 3, 0, 0));
// }

// void loop () {
//   DateTime now = rtc.now();
//   Serial.print("Date & Time: ");
//   Serial.print(now.year(), DEC);
//   Serial.print('/');
//   Serial.print(now.month(), DEC);
//   Serial.print('/');
//   Serial.print(now.day(), DEC);
//   Serial.print(" (");
//   Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//   Serial.print(") ");
//   Serial.print(now.hour(), DEC);
//   Serial.print(':');
//   Serial.print(now.minute(), DEC);
//   Serial.print(':');
//   Serial.println(now.second(), DEC);

//   delay(1000); // delay 1 seconds
// }



//--------------Voltage-----------------------------------------
// int voltagePin = A11; // analog input pin to read voltage
// int thresholdLow = 4.5; // set low voltage threshold
// int thresholdHigh = 5.5; // set high voltage threshold

// void setup() {
//   Serial.begin(9600); // initialize serial communication
// }

// void loop() {
//   int voltageValue = analogRead(voltagePin); // read voltage value
//   float voltage = voltageValue * (5.0 / 1023.0); // convert voltage value to voltage
//   Serial.print("Raw value: ");
//   Serial.print(voltageValue);
//   Serial.print(" - Voltage: ");
//   Serial.print(voltage);
//   Serial.println("V");
  
//   if (voltage < thresholdLow) {
//     Serial.println("Low voltage detected!");
//     // code to trigger alarm or take action
//   }
  
//   if (voltage > thresholdHigh) {
//     Serial.println("High voltage detected!");
//     // code to trigger alarm or take action
//   }
  
//   delay(1000); // wait for 1 second before reading voltage again
// }
