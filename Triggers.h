#ifndef __GUARD_TRIGGERS
#define __GUARD_TRIGGERS

#include <inttypes.h>
#include "settings.h"

/*
 * Simplified Trigger Manager
 * --------------------------
 * 
 * - lets you pulse pins high with a defined length
 * - all pins defined by defines inside CPP file
 */

class Triggers {
public:
  static const uint16_t defaultDuration = 20;
  static const uint8_t numbChannels = numbVoices;
private:
  struct PinSettings_t {
  	uint8_t   PinIndex;
  	volatile uint8_t* DDR_REG;
  	volatile uint8_t* PORT_REG;
  };
  static const PinSettings_t pins[numbChannels];

public:

  static void init();
  static void trigger(uint8_t, uint16_t duration = defaultDuration);
  static void giveTime();
  
private:
  static uint16_t getTime();
  static struct Timing_t {
    uint16_t offTime;
    bool isOn;
  } timing[numbChannels];
 
};


#endif
