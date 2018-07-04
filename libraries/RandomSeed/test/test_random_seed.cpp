#ifdef UNIT_TEST

#include <unity.h>
#include <RandomSeed.h>


/**
 * This test relies on the fact that getting a random number between 0 and 1000 on a 31 bit integer happens about
 * 1 in 2 million times. The chances for this happening 10 times in a row is extremly unlikely, but in theory
 * this test may generate a false positive. The chances for this happening is 1 in 16.455 * 10^62
 */
void test_random_seed_random() {
  RandomSeed randomSeed = RandomSeed(0);
  long maxSeed = 0;
  for(int i = 0; i < 10; i++) {
    long seed = randomSeed.seed();
    maxSeed = seed > maxSeed ? seed : maxSeed;
  }
  TEST_ASSERT_TRUE(maxSeed > 1000);
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_random_seed_random);
  UNITY_END();
}

void loop() {
}

#endif