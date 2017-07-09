#include "VoiceSettings.h"
#include "pattern.h"
#include "SwitchReader.h"

const uint8_t numbVoices = 6;

VoiceSettings_t voiceSettings[numbVoices];

void setup() {
  // TODO: disable millis timer?
  
  // TODO: set up voice settings (patterns and output Channel)
  
  SwitchReader::init();
  
}

uint8_t currentStepIndex = 0;
uint32_t lastPatternChangeInTicks = 0;
const uint32_t timeoutInTicks = 1000;

void loop() {
  
  // while next step is not there yet
  SwitchReader::giveTime();
  // - give time to trigger manager
  
  // proceed to next Step
  currentStepIndex++;
  if (currentStepIndex == numbStepsPerPattern) currentStepIndex = 0;
  
  // change Patterns
  for (uint8_t voiceIndex = 0; voiceIndex < numbVoices; voiceIndex++) {
    bool anyPatternChanged = false;

    if (SwitchReader::hasSwitchMoved(voiceIndex)) {
      uint8_t newSwitchPosition;
      voiceSettings[voiceIndex].setActivePatternByIndex(newSwitchPosition);
      voiceSettings[voiceIndex].setMute(false);      
      anyPatternChanged = true;
    }
    
    if (anyPatternChanged) {
      // TODO: update lastPatternChangeInTicks
    } else {
      // TODO: check difference between now and lastPatternChangeInTicks
      if (1) {
        // mute all voices
        for (uint8_t voiceIndex = 0; voiceIndex < numbVoices; voiceIndex++) {
          voiceSettings[voiceIndex].setMute(true);
        }
      }      
    }    
  }
  
  // evaluate steps
  for (uint8_t voiceIndex = 0; voiceIndex < numbVoices; voiceIndex++) {
    PatternStep_t thisStep = voiceSettings[voiceIndex].evaluateStep(currentStepIndex);
    if (thisStep != OffStep) {
      // TODO: fire trigger manager for the voice's channel with the step value
    }
   }
  
  
  
  
  
}
