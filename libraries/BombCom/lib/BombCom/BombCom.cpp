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
void BombComType::read() {
  State state = BombCom._bombProtocol->status();
  char states[] = {state.moduleState, (char) state.strikeCount, '\0'};
  Wire.write(states);
}

/**
 * Recieve bytes from the controller.
 *
 * Expected format: (OP)(DATA)
 *
 * @param numBytes the number of bytes to read.
 */
// Slave write
void BombComType::receive(int numBytes) {
  if (Wire.available()) {
    char operation = (char) Wire.read();
    if (operation == OPERATION_SERIAL_NUMBER) {
      BombCom._bombProtocol->serialNumber(readBytes(numBytes));
    }
  }
}

String BombComType::readBytes(int numBytes) {
  String s;
  s.reserve(static_cast<unsigned int>(numBytes));
  while (Wire.available()) {
    s += (char) Wire.read();
  }
  return s;

//  if (Wire.available()) {
//    char *buf = new char[numBytes];
//    int i = 0;
//    while (Wire.available()) {
//      buf[i++] = (char) Wire.read();
//    }
//    buf[i] = '\0';
//    return buf;
//  } else {
//    return {'\0'};
//  }
}

void BombComType::begin(int i2cAddress, BombProtocol *bombProtocol) {
  BombCom._bombProtocol = bombProtocol;
  Wire.begin(i2cAddress);
  Wire.onRequest(read);
  Wire.onReceive(receive);
}

BombComType BombCom = BombComType();