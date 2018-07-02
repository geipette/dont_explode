#include <Arduino.h>
#include "../lib/RandomSeed/RandomSeed.h"

/*
 * The usual way to initialize a random seed on an arinuo is to read an analog pin to get a fairly random number
 * to use as a seed.
 *
 * Reading from the analog port 10 times with a 500 ms delay gives the readings:
 * 474, 444, 421, 398, 378, 359, 341, 325, 312, 301
 *
 * In my experience the number vary between 300 and 500 and this limits the "randomness" to about 200 pseudorandom
 * sequences.
 *
 * This library aims to solve this by generating a real random number by doing a analogRead per bit of a long.
 * Each bit is the combined into a random 31 bit long that is used as the random random.
 *
 * You can either use this to get a real random number each tim
 *
 * Example usage:
 * RandomSeed seedInit = RandomSeed(0); // Supply the analog pin to use
 * randomSeed(seedInit.seed()); // Initialize arduino pseudorandom generator with a better random seed
 */

RandomSeed seedInit = RandomSeed(0);

void setup() {
  // Initialize tha pseudorandom random with a 31 bit random
  randomSeed(seedInit.seed());
}

void loop() {
  Serial.begin(9600);
  Serial.println("Random number (1-100): " + random(1, 100));
}