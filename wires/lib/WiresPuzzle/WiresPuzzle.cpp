#include "WiresPuzzle.h"
#include <RandomSeed.h>

WiresPuzzle::WiresPuzzle(String serial) {
  randomSeed(RandomSeed(0).seed()); // Generate a real 31 bit random seed and initialize
  _serial = serial;
  reset();
}

void WiresPuzzle::reset() {
  for (auto &_ledColor : _ledColors) {
    _ledColor = LED_COLORS[random(5)];
  }

  randomSwitchOff();
}


LedColor *WiresPuzzle::ledColors() {
  return _ledColors;
}

bool WiresPuzzle::check(int wirePos) {
  int blackCount = count(BLACK);
  if (blackCount == 3) {
    if (count(RED) == 0) {
      return wirePos == 1;
    } else if (_ledColors[5] == WHITE) {
      return wirePos == 5;
    } else if (count(BLUE) > 1) {
      return wirePos == posOfLast(BLUE);
    } else {
      return wirePos == 5;
    }
  } else if (blackCount == 2) {
    if (count(RED) > 1 && isLastSerialDigitOdd()) {
      return wirePos == posOfLast(RED);
    } else if (_ledColors[posOfLastNot(BLACK)] == YELLOW && count(RED) == 0) {
      return wirePos == posOfFirstNot(BLACK);
    } else if (count(BLUE) == 1) {
      return wirePos == 0;
    } else if (count(YELLOW) > 1) {
      return wirePos == 5;
    } else {
      return wirePos == 1;
    }
  } else if (blackCount == 1) {
    if (_ledColors[5] == GREEN && isLastSerialDigitOdd()) {
      return wirePos == 3;
    } else if (count(RED) == 1 && count(YELLOW) > 1) {
      return wirePos == 0;
    } else if (count(GREEN) == 0) {
      return wirePos == 1;
    } else {
      return wirePos == 0;
    }
  } else {
    if (count(YELLOW) == 0 && isLastSerialDigitOdd()) {
      return wirePos == 2;
    } else if (count(YELLOW) == 1 && count(WHITE) > 1) {
      return wirePos == 3;
    } else if (count(RED) == 0) {
      return wirePos == 5;
    } else {
      return wirePos == 3;
    }
  }

}

int WiresPuzzle::count(LedColor color) {
  int count = 0;
  for (int i = 0; i < 6; i++) {
    if (color == _ledColors[i]) {
      count++;
    }
  }
  return count;
}

int WiresPuzzle::posOfLast(LedColor color) {
  for (int i = 5; i > -1; i--) {
    if (color == _ledColors[i]) {
      return i;
    }
  }
  return -1;
}

bool WiresPuzzle::isLastSerialDigitOdd() {
  char lastDigit = 0;
  for (auto &&c : _serial) {
    if (isdigit(c)) {
      lastDigit = c;
    }
  }
  return lastDigit % 2 != 0;
}

int WiresPuzzle::posOfLastNot(LedColor color) {
  for (int i = 5; i > -1; i--) {
    if (color != _ledColors[i]) {
      return i;
    }
  }
  return -1;
}

int WiresPuzzle::posOfFirstNot(LedColor color) {
  for (int i = 0; i < 6; i++) {
    if (color != _ledColors[i]) {
      return i;
    }
  }
  return -1;
}

void WiresPuzzle::randomSwitchOff() {
  int ledPosArray[] = {0, 1, 2, 3, 4, 5};

  const size_t n = sizeof(ledPosArray) / sizeof(ledPosArray[0]);

  for (size_t i = 0; i < n - 1; i++) {
    size_t j = random(1, n - i);

    int t = ledPosArray[i];
    ledPosArray[i] = ledPosArray[j];
    ledPosArray[j] = t;
  }

  int unlitCount = random(4);
  for (int i = 0; i < unlitCount; i++) {
    _ledColors[ledPosArray[i]] = BLACK;
  }
}
