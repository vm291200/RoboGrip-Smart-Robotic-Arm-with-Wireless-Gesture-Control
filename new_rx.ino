#include <SoftwareSerial.h>
#include <Servo.h>

// HC-12 module
SoftwareSerial hc12(2, 3); // RX, TX

// Servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);

  // Attach servos to pins
  servo1.attach(6);  // Change the pin numbers based on your setup
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
}

void loop() {
  if (hc12.available() > 0) {
    Serial.println("Data incoming");
    String data = hc12.readStringUntil('\n');

    // Separate and extract sensor values
    int flex1Value = getValue(data, "F1:");
    int flex2Value = getValue(data, "F2:");
    int flex3Value = getValue(data, "F3:");
    int xValue = getValue(data, "X:");
    int yValue = getValue(data, "Y:");
    int zValue = getValue(data, "Z:");

    // Print individual sensor values
    Serial.print("Flex 1: ");
    Serial.print(flex1Value);
    Serial.print("\tFlex 2: ");
    Serial.print(flex2Value);
    Serial.print("\tFlex 3: ");
    Serial.print(flex3Value);
    Serial.print("\tX: ");
    Serial.print(xValue);
    Serial.print("\tY: ");
    Serial.print(yValue);
    Serial.print("\tZ: ");
    Serial.println(zValue);

    // Map sensor values to servo angles (adjust these values based on your setup)
    int angle1 = map(flex1Value, 750, 900, 0, 180);
    int angle2 = map(flex2Value, 500, 900, 0, 180);
    int angle3 = map(flex3Value, 750, 900, 0, 180);
    int angle4 = map(xValue, 300, 500, 0, 180);
    Serial.println(angle1);
    Serial.println(angle2);
    Serial.println(angle3);
    Serial.println(angle4);
    // Control servos
    servo1.write(angle1);
    servo2.write(angle2);
    servo3.write(angle3);
    servo4.write(angle4);
  }
}

// Function to extract sensor values from the received data
int getValue(String data, String identifier) {
  int start = data.indexOf(identifier) + identifier.length();
  int end = data.indexOf(',', start);
  if (end == -1) {
    end = data.length() - 1;
  }
  String valueStr = data.substring(start, end);
  return valueStr.toInt();
}
