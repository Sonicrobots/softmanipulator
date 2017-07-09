#include "SwitchReader.h"
#include <string.h>

uint8_t SwitchReader::states[numbSwitches];
uint8_t SwitchReader::oldStates[numbSwitches];
bool SwitchReader::changedFlags[numbSwitches];

uint8_t SwitchReader::currentSwitchIndex;


void SwitchReader::init() {
  // set up AD converter
  ADMUX  = (1<<REFS0);	    // external reference voltage
  ADMUX |= (1<<ADLAR);      // adjust result to left
  ADCSRA  = (1<<ADEN);      // enable ADC
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1);	// prescaler
  
  // start conversion for index 0
  currentSwitchIndex = 0;
  setMultiplexerFromCurrentSwitchID();
  startADConversion();
  
  // convert all the switches until we reach 0 again
  while (currentSwitchIndex != 0) {
    // wait for conversion to finish
    while (!(ADCSRA & (1<<ADIF)));
    // process result (also proceeds to next switch)
    processConversionResult();
  }
  
  // clear changed flags
  // they might have been set by comparing initial conversions
  // with unitialized oldStates
  memset(changedFlags, 0, sizeof(changedFlags));  
}

void SwitchReader::giveTime() {
  
  // as long as AD conversion is running, there is nothing to be done
  if (!(ADCSRA & (1<<ADIF))) return;
  
  processConversionResult();
}

void SwitchReader::processConversionResult() {
  
  // shift back current state to old one
  oldStates[currentSwitchIndex] = states[currentSwitchIndex];
  
  // read result and quantize
  states[currentSwitchIndex] = quantizeADValueToSwitchPosition(ADCH);

  // set changed flagsfs
  if (states[currentSwitchIndex] != oldStates[currentSwitchIndex]) {
    changedFlags[currentSwitchIndex] = true;
  }

  // proceed to next switch
  currentSwitchIndex++;
  if (currentSwitchIndex >= numbSwitches) currentSwitchIndex = 0;  

  // set up multiplexer and start new conversion
  setMultiplexerFromCurrentSwitchID();
  startADConversion();

}

void SwitchReader::startADConversion() {
  ADCSRA |= (1 << ADSC);
}
void SwitchReader::setMultiplexerFromCurrentSwitchID() {
  ADMUX &= ~(0b00001111);
  ADMUX |= currentSwitchIndex;
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
  
  // return and clear flag
  if (changedFlags[switchIndex]) {
    changedFlags[switchIndex] = false;
    return true;
  } else{
    return false;
  }
}
