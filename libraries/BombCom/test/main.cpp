#ifdef UNIT_TEST

#include <unity.h>
#include "Wire.h"
#include <BombCom.h>
#include <Arduino.h>

#define MY_I2C_ADDRESS 8

String bombSerial = "not initialized.";

class MyBombProtocol : public BombProtocol {
  State status() override {
    return State(MODULE_STATE_INITIALIZING, 0);
  }

  void serialNumber(const String& serial) override {
    bombSerial = serial;
  }

};


MyBombProtocol myBombProtocol = MyBombProtocol();

void test_recieve_serial() {
  uint8_t serial[] = "sa12uuukll882";
  Wire.onReceiveService(serial, 13);

  TEST_ASSERT_TRUE(bombSerial == "a12uuukll882");
}

void test_poll_status() {
//  Wire.onRequestService();
}

void setup() {
  delay(2000);
  Serial.begin(9600);
  BombCom.begin(MY_I2C_ADDRESS, &myBombProtocol);
  UNITY_BEGIN();

  RUN_TEST(test_recieve_serial);
  RUN_TEST(test_poll_status);

  UNITY_END();
}

void loop() {
}

#endif