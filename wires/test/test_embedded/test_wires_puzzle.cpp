#ifdef UNIT_TEST

#include <unity.h>
#include "WiresPuzzle.h"

void test_last_serial_digit_is_odd() {
  WiresPuzzle* wiresPuzzle = new WiresPuzzle("uxb123");
  TEST_ASSERT_TRUE(wiresPuzzle->isLastSerialDigitOdd());

  wiresPuzzle = new WiresPuzzle("uxb123abc");
  TEST_ASSERT_TRUE(wiresPuzzle->isLastSerialDigitOdd());

  wiresPuzzle = new WiresPuzzle("uxb1234");
  TEST_ASSERT_FALSE(wiresPuzzle->isLastSerialDigitOdd());

  wiresPuzzle = new WiresPuzzle("uxb1234abc");
  TEST_ASSERT_FALSE(wiresPuzzle->isLastSerialDigitOdd());

}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_last_serial_digit_is_odd);
  UNITY_END();
}

void loop() {

}



#endif