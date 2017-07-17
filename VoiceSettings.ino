#include "VoiceSettings.h"
#include <string.h>

#define DEBUG

void VoiceSettings_t::selectPatterns(Pattern_t * newPatterns[]) {
  memcpy(patterns, newPatterns, sizeof(Pattern_t*)*numbPatternsPerVoice);
  
  #ifdef DEBUG
  Serial.println("Patterns loaded in this voice:");
  for (uint8_t p=0; p<numbPatternsPerVoice; p++) {
    setActivePatternByIndex(p);
    Serial.print(p); Serial.print(" at Addr "); Serial.print(uint32_t(patterns[p])); Serial.print(": ");
    for (uint8_t s=0; s<numbStepsPerPattern; s++) {
      Serial.print(evaluateStep(s));
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
  #endif
  
  setActivePatternByIndex(0);
}

void VoiceSettings_t::setOutputChannel(uint8_t val) {
  outputChannel = val;
}
uint8_t VoiceSettings_t::getOutputChannel() {
  return outputChannel;
}

void VoiceSettings_t::setMute(bool val) {
  muted = val;
}

void VoiceSettings_t::setActivePatternByIndex(uint8_t val) {
  activePatternIndex = val;
}
uint8_t VoiceSettings_t::getActivePatternIndex() {
  return activePatternIndex;
}

PatternStep_t VoiceSettings_t::evaluateStep(uint8_t stepNumber) {
  if (!muted) {
    return (*patterns[activePatternIndex]).steps[stepNumber];
  } else {
    return OffStep;
  }
}

