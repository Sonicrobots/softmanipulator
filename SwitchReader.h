#ifndef __GUARD_SWITCH_READER
#define __GUARD_SWITCH_READER

#include <inttypes.h>
#include "settings.h"

class SwitchReader {
public:
  static void init();
  static void giveTime();
  
  static const uint8_t numbPositions = 6;
  static const uint8_t numbSwitches = numbVoices;
  
  static uint8_t getPosition(uint8_t switchIndex);
  static bool hasSwitchMoved(uint8_t switchIndex);
  
private:

  static void processConversionResult();
    
  static uint8_t quantizeADValueToSwitchPosition(uint8_t);
  static void setMultiplexerFromCurrentSwitchID();
  static void startADConversion();

  static uint8_t currentConvertingSwitchIndex;
  
  
  static uint8_t states[numbSwitches];
  static uint8_t oldStates[numbSwitches];
};

#endif
