#ifndef BombCom_H
#define BombCom_H

#include <WString.h>

#define MODULE_STATE_INITIALIZING 'i'
#define MODULE_STATE_ACTIVE 'a'
#define MODULE_STATE_DEFUSED 'd'

#define OPERATION_SERIAL_NUMBER 's'
#define OPERATION_RESET 'r'

/*
 * The aim of this is to encapsulate the expected communication between bomb modules. All modules except the controller
 * should implement a BombProtocol and call BombCom.begin(...)
 */
 
/**
  * The current state of a bomb module.
  *
  * moduleState can be: MODULE_STATE_INITIALIZING, MODULE_STATE_ACTIVE or MODULE_STATE_DEFUSED
  * strikeount is the number of "strikes" a module has registered.
  *
  * A module should usually not switch from initializing to active before it has recieved the serial number from the
  * controller.
  */
struct State {
  char moduleState;
  uint8_t strikeCount;

  State(char moduleState, uint8_t strikeCount) {
    this->moduleState = moduleState;
    this->strikeCount = strikeCount;
  }
};


/**
 * It is expected that all modules implements this.
 */
class BombProtocol {
public:
  virtual State status();
  virtual void serialNumber(const String& serial);
};

class BombComType {
private:
  BombProtocol* _bombProtocol;
  static void read();
  static void receive(int numBytes);
  static String readBytes(int numBytes);

public:
  void begin(int i2cAddress, BombProtocol* bombProtocol);

};


extern BombComType BombCom;

#endif //BombComType_H
