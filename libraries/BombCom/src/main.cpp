#include <Arduino.h>
#include <BombCom.h>

#define MY_I2C_ADDRESS 8

String bombSerial = "not initialized.";

class MyBombProtocol : public BombProtocol {
  State* status() override {
    return new State(MODULE_STATE_INITIALIZING, 0);
  }

  void serialNumber(String serial) override {
    bombSerial = serial;
  }

};

MyBombProtocol myBombProtocol = MyBombProtocol();

BombCom* bombCom = BombCom::createInstance(MY_I2C_ADDRESS, &myBombProtocol);


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Serial number is: " + bombSerial);
  delay(5000);
}