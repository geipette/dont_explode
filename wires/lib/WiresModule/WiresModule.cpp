#include <Arduino.h>
#include "WiresModule.h"

#define MCP_I2C_ADDRESS 0

WiresModule::WiresModule() {
  _puzzle = new WiresPuzzle("acb");
  _mcp = new Adafruit_MCP23017();
  _mcp->begin(MCP_I2C_ADDRESS);
  _mcp->pinMode(0, OUTPUT);
  _mcp->pinMode(1, OUTPUT);
  _mcp->pinMode(2, OUTPUT);
  _mcp->pinMode(3, OUTPUT);
  _mcp->pinMode(4, OUTPUT);
  _mcp->pinMode(5, OUTPUT);
  _mcp->pinMode(6, OUTPUT);
  _mcp->pinMode(7, OUTPUT);
  _mcp->pinMode(8, OUTPUT);
  _mcp->pinMode(9, OUTPUT);
  _mcp->pinMode(10, OUTPUT);
  _mcp->pinMode(11, OUTPUT);
  _mcp->pinMode(12, OUTPUT);
  _mcp->pinMode(13, OUTPUT);
  _mcp->pinMode(14, OUTPUT);
  _mcp->pinMode(15, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void WiresModule::setLed(int pos, LedColor ledColor) {
  Serial.print("Setting led" + String(pos));
  Serial.println(" to " + ledColor.name);
  setPin(_ledAddressBook.redLed(pos), ledColor.r);
  setPin(_ledAddressBook.greenLed(pos), ledColor.g);
  setPin(_ledAddressBook.blueLed(pos), ledColor.b);
}

void WiresModule::setPin(LedAddress ledAddress, bool colorState) const {
  if (ledAddress.onMcp) {
    _mcp->digitalWrite(ledAddress.pin, colorState ? LOW : HIGH);
  } else {
    digitalWrite(ledAddress.pin, colorState ? LOW : HIGH);
  }
}

bool WiresModule::check(int wirePos) {
  return _puzzle->check(wirePos);
}

void WiresModule::begin() {
  for (int i = 0; i < 6; ++i) {
    setLed(i, _puzzle->ledColors()[i]);
  }
}

void WiresModule::singleLedLight(int ledPos) {
  for (int i = 0; i < 6; ++i) {
    setLed(i, BLACK);
  }
  setLed(ledPos, WHITE);
}
