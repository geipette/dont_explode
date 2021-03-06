#include <Arduino.h>
#include <BombCom.h>

#define MY_I2C_ADDRESS 8

String bombSerial = "not initialized.";

class MyBombProtocol : public BombProtocol {
  State status() override {
    return {MODULE_STATE_INITIALIZING, 0};
  }

  void serialNumber(const String& serial) override {
    bombSerial = serial;
  }

};

MyBombProtocol myBombProtocol = MyBombProtocol();

void setup() {
  Serial.begin(9600);
  BombCom.begin(MY_I2C_ADDRESS, &myBombProtocol);
}

void loop() {
  Serial.println("Serial number is: " + bombSerial);
  delay(5000);
}