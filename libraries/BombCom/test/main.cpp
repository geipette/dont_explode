#ifdef UNIT_TEST

#include <unity.h>
#include "Wire.h"
#include <BombCom.h>
#include <Arduino.h>

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


void test_recieve_serial() {
  uint8_t serial[] = "sa12uuukll882";
  Wire.onReceiveService(serial, 13);

  TEST_ASSERT_TRUE(bombSerial == "a12uuukll882");
}

void test_poll_status() {
  Wire.onRequestService();
  auto size = WireMock_writtenWireSize;
  auto data = WireMock_writtenWireData;

  TEST_ASSERT_TRUE(size == 2);
  TEST_ASSERT_TRUE(data == "i0");

}

void setup() {
  delay(2000);
  Serial.begin(9600);
  UNITY_BEGIN();

  RUN_TEST(test_recieve_serial);
  RUN_TEST(test_poll_status);

  UNITY_END();
}

void loop() {
}

#endif