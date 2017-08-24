#include "SwitchReader.h"
#include <string.h>

uint8_t SwitchReader::states[numbSwitches];
uint8_t SwitchReader::oldStates[numbSwitches];
uint8_t SwitchReader::currentConvertingSwitchIndex;

//#define DEBUG_SWITCHES


void SwitchReader::init() {
  // set up AD converter
  ADMUX  = (1<<REFS0);	    // external reference voltage
  ADMUX |= (1<<ADLAR);      // adjust result to left
  ADCSRA  = (1<<ADEN);      // enable ADC
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1);	// prescaler
  
  // start conversion for index 0
  currentConvertingSwitchIndex = 0;
  setMultiplexerFromCurrentSwitchID();
  startADConversion();
  
  // read all switches once
  for (uint8_t s=0; s<numbSwitches; s++) {
    // wait for conversion to finish
    while (!(ADCSRA & (1<<ADIF)));
    // process result (also proceeds to next switch)
    processConversionResult();
  }
  
  #ifdef DEBUG_SWITCHES
  for (uint8_t s=0; s<numbSwitches; s++) {
    Serial.print("Sw ");Serial.print(s);Serial.print(" initially ");Serial.println(states[s]);
  }
  #endif
  
  // set old states like new states to avoid triggering
  // right after startup
  memcpy(oldStates, states, sizeof(oldStates));
}

void SwitchReader::giveTime() {
  
  // as long as AD conversion is running, there is nothing to be done
  if (!(ADCSRA & (1<<ADIF))) return;
  
  processConversionResult();
}

void SwitchReader::processConversionResult() {
  
  // read result and quantize
  states[currentConvertingSwitchIndex] = quantizeADValueToSwitchPosition(ADCH);

  // proceed to next switch
  currentConvertingSwitchIndex++;
  if (currentConvertingSwitchIndex >= numbSwitches) currentConvertingSwitchIndex = 0;  

  // set up multiplexer and start new conversion
  setMultiplexerFromCurrentSwitchID();
  startADConversion();
}

void SwitchReader::startADConversion() {
  ADCSRA |= (1 << ADSC);
}
void SwitchReader::setMultiplexerFromCurrentSwitchID() {
  ADMUX &= ~(0b00001111);
  ADMUX |= currentConvertingSwitchIndex;
}
uint8_t SwitchReader::quantizeADValueToSwitchPosition(uint8_t val) {
  const uint8_t stepSize = (256 + numbPositions/2) / numbPositions;  
  return val / stepSize;
}


uint8_t SwitchReader::getPosition(uint8_t switchIndex) {
  if (switchIndex >= numbSwitches) return 0;
  
  return states[switchIndex];
}

bool SwitchReader::hasSwitchMoved(uint8_t switchIndex) {

  if (switchIndex >= numbSwitches) return 0;
  
  // check if switch position changed since last comparison
  if (states[switchIndex] != oldStates[switchIndex]) {
    
    #ifdef DEBUG_SWITCHES
    Serial.print("Sw ");Serial.print(switchIndex);Serial.print(" changed from ");Serial.print(oldStates[switchIndex]);Serial.print(" to ");Serial.println(states[switchIndex]);
    #endif
    
    // shift back current state to old one
    oldStates[switchIndex] = states[switchIndex];
    
    return true;    
  }  
  return false;
}
