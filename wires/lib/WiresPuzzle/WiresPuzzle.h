#ifndef WiresPuzzle_h
#define WiresPuzzle_h

#include <Arduino.h>

#define WHITE  LedColor(true, true, true, "white")
#define RED    LedColor(true, false, false, "red")
#define BLUE   LedColor(false, false, true, "blue")
#define YELLOW LedColor(true, true, false, "yellow")
#define GREEN  LedColor(false, true, false, "green")
#define BLACK  LedColor(false, false, false, "black")

struct LedColor {
  bool r, g, b;
  String name;

  LedColor(bool ir, bool ig, bool ib, String iName) {
    r = ir;
    g = ig;
    b = ib;
    name = iName;
  };

  bool operator==(const LedColor &rhs) const {
    return r == rhs.r && g == rhs.g && b == rhs.b;
  }

  bool operator!=(const LedColor &rhs) const {
    return r != rhs.r || g != rhs.g || b != rhs.b;
  }

};

const LedColor LED_COLORS[] = {WHITE, RED, BLUE, YELLOW, GREEN, BLACK};

class WiresPuzzle {
public:
  WiresPuzzle(String serial);

  void reset();

  LedColor *ledColors();

  bool check(int wirePos);

  bool isLastSerialDigitOdd();

private:

  int count(LedColor color);

  int posOfLast(LedColor color);

  int posOfLastNot(LedColor color);

  int posOfFirstNot(LedColor color);

  String _serial;

  LedColor _ledColors[6] = {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

  void randomSwitchOff();
};

#endif
