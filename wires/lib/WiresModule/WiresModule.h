#ifndef WiresModule_h
#define WiresModule_h

#include <Adafruit_MCP23017.h>
#include <Arduino.h>
#include <WiresPuzzle.h>

struct LedAddress {
  bool empty = false;
  bool onMcp;
  uint8_t pin;

  LedAddress(bool iOnMcp, uint8_t iPin) {
    onMcp = iOnMcp;
    pin = iPin;
  }

};

struct LedAddressBook {
  LedAddress redLed(int pos) {
    switch (pos) {
      case 0:
        return LedAddress(true, 0);
      case 1:
        return LedAddress(true, 3);
      case 2:
        return LedAddress(true, 6);
      case 3:
        return LedAddress(true, 9);
      case 4:
        return LedAddress(true, 12);
      case 5:
        return LedAddress(true, 15);
      default:
        return LedAddress(false, 0);
    }
  }

  LedAddress greenLed(int pos) {
    switch (pos) {
      case 0:
        return LedAddress(false, 8);
      case 1:
        return LedAddress(true, 2);
      case 2:
        return LedAddress(true, 5);
      case 3:
        return LedAddress(true, 8);
      case 4:
        return LedAddress(true, 11);
      case 5:
        return LedAddress(true, 14);
      default:
        return LedAddress(false, 0);
    }
  }

  LedAddress blueLed(int pos) {
    switch (pos) {
      case 0:
        return LedAddress(false, 9);
      case 1:
        return LedAddress(true, 1);
      case 2:
        return LedAddress(true, 4);
      case 3:
        return LedAddress(true, 7);
      case 4:
        return LedAddress(true, 10);
      case 5:
        return LedAddress(true, 13);
      default:
        return LedAddress(false, 0);
    }
  }
};

class WiresModule {
public:
  WiresModule();

  bool check(int wirePos);

  void begin();

  void singleLedLight(int ledPos);

private:
  LedAddressBook _ledAddressBook;
  WiresPuzzle *_puzzle;
  Adafruit_MCP23017 *_mcp;

  void setLed(int pos, LedColor ledColor);

  void setPin(LedAddress ledAddress, bool colorState) const;
};

#endif
