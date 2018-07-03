#ifndef BOMBCOM_H
#define BOMBCOM_H

#include <WString.h>

#define MODULE_STATE_INITIALIZING 'i'
#define MODULE_STATE_ACTIVE 'a'
#define MODULE_STATE_DEFUSED 'd'

#define OPERATION_SERIAL_NUMBER 's'

/**
 * Because of my inability to pass a lambda with capture or a function pointer to a member function I have
 * worked around this by making all relevant callbacks static. This has the effect that The BombCom class
 * must be a singleton. Hoping to solve this in the future.
 */

struct State {
  char moduleState;
  uint8_t strikeCount;

  State(char moduleState, uint8_t strikeCount) {
    this->moduleState = moduleState;
    this->strikeCount = strikeCount;
  }
};

class BombProtocol {
public:
  virtual State* status();
  virtual void serialNumber(String serial);
};

class BombCom {
private:
  BombProtocol* _bombProtocol;
  static BombCom* instance;

  BombCom(int i2cAddress, BombProtocol* bombProtocol);
  static void read();
  static void receive(int numBytes);
  static char* readBytes(int numBytes);

public:
  static BombCom* createInstance(int i2cAddress, BombProtocol* bombProtocol);
  static BombCom* getInstance();


};


#endif //BOMBCOM_H
