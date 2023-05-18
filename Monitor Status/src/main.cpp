#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>
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

//---------------Timer Interrupt----------------------------

#include <TimerOne.h>
#define ledPin 4
int ledState = LOW;
int sensorPin = A9;// chân analog kết nối tới cảm biến LM35
RTC_DS1307 rtc;
DateTime now; // Get the current time from the RTC module
DateTime start_time;
int voltagePin = A11; // analog input pin to read voltage
int resetCount;
void blinkLed(){
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
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
  Serial.print("Timer interrupt: ");
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

  Wire.begin();
  rtc.begin();

  // Set the time when the board is powered on
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  start_time = rtc.now();
  resetCount = EEPROM.read(0);
  resetCount++;
  EEPROM.write(0, resetCount);
}

void loop() {
  now = rtc.now();
}



//---------Waiting for command-----------------------------
// RTC_DS1307 rtc;
// bool Job = false;
// int year, month, day, hour, minute, second;
// void processSerialData(String serialData) {
//   // Split the serial data by semicolon
//   int separatorIndex = serialData.indexOf(';');
//   if (separatorIndex >= 0) {
//     String command = serialData.substring(0, separatorIndex);
//     String timeValue = serialData.substring(separatorIndex + 1);
    
//     // Print the command and time values
//     // Serial.print("Command: ");
//     // Serial.println(command);
//     // Serial.print("Time: ");
//     Serial.println(timeValue);
//     year = atoi(timeValue.substring(0, 5).c_str());
//     month = atoi(timeValue.substring(6, 8).c_str());
//     day = atoi(timeValue.substring(9, 11).c_str());
//     hour = atoi(timeValue.substring(11, 14).c_str());
//     minute = atoi(timeValue.substring(15, 18).c_str());
//     second = atoi(timeValue.substring(19, 22).c_str());
//   }
  

//   // create a DateTime object from the components
// }

// void setup() {
//   Serial.begin(9600);  // Initialize serial communication
//   Wire.begin();        // Initialize I2C communication
//   pinMode(LED_BUILTIN, OUTPUT);
//   rtc.begin();
//   rtc.adjust(DateTime(F(__DATE__), F("15:53:00")));
// }
// void loop() {
//   if (Serial.available()) {
//     String serialData = Serial.readStringUntil('\n');
//     processSerialData(serialData);   
//     Job = true;
//   }
//   if (Job == true){
//     DateTime startDateTime(year, month, day, hour, minute, second);
//     Serial.print("Year: ");
//     Serial.print(year);
//     Serial.print('/');
//     Serial.print("Month: ");
//     Serial.print(month);
//     Serial.print('/');
//     Serial.print("Day: ");
//     Serial.print(day);
//     Serial.print('/');
//     Serial.print("H: ");
//     Serial.print(hour);
//     Serial.print(':');
//     Serial.print("M: ");
//     Serial.print(minute);
//     Serial.print("S: ");
//     Serial.print(':');
//     Serial.println(second);
//     // Serial.print("Date & Time: ");
//     // Serial.print(startDateTime.year(), DEC);
//     // Serial.print('/');
//     // Serial.print(startDateTime.month(), DEC);
//     // Serial.print('/');
//     // Serial.print(startDateTime.day(), DEC);
//     // Serial.print("  ");
//     // Serial.print(startDateTime.hour(), DEC);
//     // Serial.print(':');
//     // Serial.print(startDateTime.minute(), DEC);
//     // Serial.print(':');
//     // Serial.println(startDateTime.second(), DEC);
//     DateTime now = rtc.now();
//     // Serial.print("Now.sec: ");
//     // Serial.print(now.secondstime());
//     // Serial.print(" -- Start.sec: ");
//     // Serial.println(startDateTime.secondstime());
//     if (now.secondstime() >= startDateTime.secondstime()) {
//       digitalWrite(LED_BUILTIN, HIGH);
//       Serial.println("It is on scheduled time");
//       Serial.print("Date & Time: ");
//       Serial.print(now.year(), DEC);
//       Serial.print('/');
//       Serial.print(now.month(), DEC);
//       Serial.print('/');
//       Serial.print(now.day(), DEC);
//       Serial.print("  ");
//       Serial.print(now.hour(), DEC);
//       Serial.print(':');
//       Serial.print(now.minute(), DEC);
//       Serial.print(':');
//       Serial.println(now.second(), DEC);
//     } else {
//       // Turn off the LED
//       digitalWrite(LED_BUILTIN, LOW);
//       Serial.print("NOT-- ");
//       Serial.print("Date & Time: ");
//       Serial.print(now.year(), DEC);
//       Serial.print('/');
//       Serial.print(now.month(), DEC);
//       Serial.print('/');
//       Serial.print(now.day(), DEC);
//       Serial.print("  ");
//       Serial.print(now.hour(), DEC);
//       Serial.print(':');
//       Serial.print(now.minute(), DEC);
//       Serial.print(':');
//       Serial.println(now.second(), DEC);
//     }
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
