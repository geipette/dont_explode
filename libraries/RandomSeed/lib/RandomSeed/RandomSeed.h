#ifndef RANDOMSEED_H
#define RANDOMSEED_H

#include <Arduino.h>

#define RANDOMSEED_NUMBER_OF_BITS 31

class RandomSeed {
public:
  /**
   * Supply a non connected analog pin for best results.
   * @param analogPin
   */
  RandomSeed(uint8_t analogPin);
  unsigned long seed();

private:
  unsigned int bitOut(void);

  uint8_t _analogPin;
};


#endif //RANDOMSEED_H
