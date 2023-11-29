#include <SoftwareSerial.h>

// HC-12 module
SoftwareSerial hc12(2, 3); // RX, TX

// Analog pins for Flex Sensors
int flexPin1 = A5;
int flexPin2 = A4;
int flexPin3 = A3;

// Analog pins for ADXL335
int xPin = A2;
int yPin = A1;
int zPin = A0;

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
}

void loop() {
  // Read sensor data
  int flexValue1 = analogRead(flexPin1);
  int flexValue2 = analogRead(flexPin2);
  int flexValue3 = analogRead(flexPin3);
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = analogRead(zPin);

  // Print sensor data to Serial Monitor
  Serial.print("Flex 1: ");
  Serial.print(flexValue1);
  Serial.print("\tFlex 2: ");
  Serial.print(flexValue2);
  Serial.print("\tFlex 3: ");
  Serial.print(flexValue3);
  Serial.print("\tX: ");
  Serial.print(xValue);
  Serial.print("\tY: ");
  Serial.print(yValue);
  Serial.print("\tZ: ");
  Serial.println(zValue);

  // Send data through HC-12
  hc12.print("F1:");
  hc12.print(flexValue1);
  hc12.print(",F2:");
  hc12.print(flexValue2);
  hc12.print(",F3:");
  hc12.print(flexValue3);
  hc12.print(",X:");
  hc12.print(xValue);
  hc12.print(",Y:");
  hc12.print(yValue);
  hc12.print(",Z:");
  hc12.println(zValue);

  delay(1000); // Adjust the delay as needed
}
