#include "RandomSeed.h"

RandomSeed::RandomSeed(uint8_t analogPin) {
  _analogPin = analogPin;
}

unsigned int RandomSeed::bitOut() {
  static unsigned long firstTime = 1, prev = 0;
  unsigned long bit1 = 0, bit0 = 0, x = 0, limit = 99;
  if (firstTime) {
    firstTime = 0;
    prev = analogRead(_analogPin);
  }
  while (limit--) {
    x = analogRead(_analogPin);
    bit1 = (prev != x ? 1 : 0);
    prev = x;
    x = analogRead(_analogPin);
    bit0 = (prev != x ? 1 : 0);
    prev = x;
    if (bit1 != bit0)
      break;
  }
  return bit1;
}

unsigned long RandomSeed::seed() {
  // return value with 'noOfBits' random bits set
  unsigned long random = 0;
  for (unsigned int i = 0; i < RANDOMSEED_NUMBER_OF_BITS; ++i) {
    random = (random << 1) | bitOut();
  }
  return random;
}
