#include "BombCom.h"
#include <Wire.h>

/**
 * Status poll from the controller.
 *
 * State: 'i' - initializing
 *        'd' - defused
 *        'a' - active
 * Expected output: (i|d|a)(0-3)
 *
 * Ex: i0 -> Initializing, 0 strikes
 * Ex2: a1 -> Active, 1 strike
 */
// Slave read
void BombCom::read() {
  BombProtocol* bombProtocol = BombCom::getInstance()->_bombProtocol;
  State *state = bombProtocol->status();
  char states[] = {state->moduleState, (char) state->strikeCount, '\0'};
  delete state;
  Wire.write(states);
}

// Slave write
void BombCom::receive(int numBytes) {
  BombProtocol* bombProtocol = BombCom::getInstance()->_bombProtocol;
  if (Wire.available()) {
    char operation = (char) Wire.read();
    if (operation == OPERATION_SERIAL_NUMBER) {
      char *bytes = readBytes(numBytes);
      bombProtocol->serialNumber(String(bytes));
      delete bytes;
    }
  }
}

char *BombCom::readBytes(int numBytes) {
  if (Wire.available()) {
    char *buf = new char[numBytes];
    int i = 0;
    while (Wire.available()) {
      buf[i++] = (char) Wire.read();
    }
    buf[i] = '\0';
    return buf;
  } else {
    return {'\0'};
  }
}

BombCom* BombCom::instance = 0;

BombCom* BombCom::getInstance() {
  return instance;
}

BombCom* BombCom::createInstance(int i2cAddress, BombProtocol *bombProtocol) {
  if (instance == 0) {
    instance = new BombCom(i2cAddress, bombProtocol);
  }
  return instance;
}

BombCom::BombCom(int i2cAddress, BombProtocol *bombProtocol) {
  _bombProtocol = bombProtocol;
  Wire.begin(i2cAddress);
  Wire.onRequest(read);
  Wire.onReceive(receive);
}