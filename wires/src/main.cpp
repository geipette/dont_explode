#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <WiresModule.h>
#include <Adafruit_NeoPixel.h>
#include <RandomSeed.h>
#include <BombCom.h>

#ifdef __AVR__

#include <avr/power.h>

#endif

#define LEDS_PIN 10

#define GREEN_COLOR leds.Color(150, 0, 0)
#define RED_COLOR   leds.Color(0, 150, 0)
#define BLUE_COLOR  leds.Color(0, 0, 150)
#define WIRES_I2C_ADDRESS 8

uint8_t WIRE_PINS[] = {2, 3, 4, 5, 6, 7};

boolean defused = false;
boolean strikes[] = {false, false, false, false, false, false};
boolean initializing = true;


int countStrikes() {
  int count = 0;
  for (bool strike : strikes) {
    if (strike) {
      count++;
    }
  }
  return count;
}

class WiresBombProtocol : public BombProtocol {

  State * status() override {
    if (initializing) {
      return new State(MODULE_STATE_INITIALIZING, 0);
    } else if (defused) {
      return new State(MODULE_STATE_DEFUSED, countStrikes());
    } else {
      return new State(MODULE_STATE_ACTIVE, countStrikes());
    }
  }

  void serialNumber(String serial) {

  }

};

WiresBombProtocol wiresBombProtocol = WiresBombProtocol();

BombCom* bombCom = BombCom::createInstance(WIRES_I2C_ADDRESS, &wiresBombProtocol);
WiresModule wires = WiresModule();
Adafruit_NeoPixel leds = Adafruit_NeoPixel(1, LEDS_PIN, NEO_GRB + NEO_KHZ800);


void checkWires() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(WIRE_PINS[i]) == LOW) {
      if (wires.check(i)) {
        defused = true;
      } else {
        strikes[i] = true;
      }
    }
  }
}

void setStatusLedState() {
  if (defused) {
    leds.setPixelColor(0, GREEN_COLOR);
  } else if (initializing) {
    leds.setPixelColor(0, BLUE_COLOR);
  } else {
    leds.setPixelColor(0, RED_COLOR);
  }
  leds.show();
}

void initialize() {
  Serial.println("Initializing...");
  bool initDone;
  int initPos = -1;
  do {
    initDone = true;
    for (int i = 0; i < 6; i++) {
      if (digitalRead(WIRE_PINS[i]) == LOW) {
        if (initPos != i) {
          wires.singleLedLight(i);
          initPos = i;
        }
        initDone = false;
        break;
      }
    }
  } while (!initDone);
  Serial.println("...done initializing");
}

void setup() {
  Serial.begin(9600);  // start serial for output
  leds.begin();
  setStatusLedState();
  for (uint8_t pin : WIRE_PINS) {
    pinMode(pin, INPUT);
  }

  initialize();
  wires.begin();
  initializing = false;
}

void loop() {
  setStatusLedState();
  checkWires();
}