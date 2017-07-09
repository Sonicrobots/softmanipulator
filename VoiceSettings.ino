#include "VoiceSettings.h"
#include <string.h>

void VoiceSettings_t::selectPatterns(Pattern_t * newPatterns) {
  memcpy(patterns, newPatterns, sizeof(Pattern_t)*numbPatternsPerVoice);
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
    return (*patterns[activePatternIndex])[stepNumber];
  } else {
    return OffStep;
  }
}

