#include "Triggers.h"
#include "portManipulations.h"

#define DEBUG

const Triggers::PinSettings_t Triggers::pins[6] = {
  {0, &DDRB, &PORTB},
  {1, &DDRB, &PORTB},
  {2, &DDRB, &PORTB},
  {3, &DDRB, &PORTB},
  {4, &DDRB, &PORTB},
  {6, &DDRD, &PORTD},
};


Triggers::Timing_t Triggers::timing[numbChannels];

void Triggers::init() {
  
  // set all pins to output
  for (uint8_t i=0; i<numbChannels; i++) {
    *(pins[i].DDR_REG) |= (1<<pins[i].PinIndex);
  }  
}

uint16_t Triggers::getTime() {
  // always use redduced version of millis
  // because handling 32bit integers is costly and
  // as pulse durations are short, the longer time until overflow is not needed
  return uint16_t(millis());
}

void Triggers::trigger(uint8_t index, uint16_t duration) {
  
  if (index < numbChannels) {

    // set pin on
    *(pins[index].PORT_REG) |= (1<<pins[index].PinIndex);  
    
    // remember the time when it needs to be turned off again
    timing[index].offTime = getTime() + duration;
    timing[index].isOn = true;
    
  } else {
    #ifdef DEBUG
    Serial.print("Trigger index "); Serial.print(index); Serial.print(" out of range");
    #endif
  }
}

void Triggers::giveTime() {
  
  // get time once and use it for all channels
  uint16_t now = getTime();
  
  // check all channels
  for (uint8_t i=0; i<numbChannels; i++) {
    
    // is it active?
    if (timing[i].isOn) {
      
      // does it need to be turned off?
      if (now >= timing[i].offTime) {
        
        // set pin off
        *(pins[i].PORT_REG) &= ~(1<<pins[i].PinIndex);
        timing[i].isOn = false;
      }
    }      
  }  
}
