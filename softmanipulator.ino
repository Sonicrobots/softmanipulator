#include "VoiceSettings.h"
#include "pattern.h"
#include "SwitchReader.h"
#include "Triggers.h"
#include "settings.h"

#define DEBUG

VoiceSettings_t voiceSettings[numbVoices];

void setup() {
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  
  SwitchReader::init();
  Triggers::init();
  
  for (uint8_t v=0; v<numbVoices; v++) {
    
    // set output channel like voice index
    voiceSettings[v].setOutputChannel(v);
    
    // create temporary array of pattern pointers
    Pattern_t* thesePatterns[VoiceSettings_t::numbPatternsPerVoice];
    
    // fill array according to selected pattern indices for this voice
    #ifdef DEBUG
    Serial.print("Patterns for voice "); Serial.print(v); Serial.print(":");
    #endif
    for (uint8_t p=0; p<VoiceSettings_t::numbPatternsPerVoice; p++) {
      uint8_t thisPatternIndex = patternsPerVoice[v][p];
      #ifdef DEBUG
      Serial.print(" "); Serial.print(thisPatternIndex);
      #endif
      thesePatterns[p] = &Patterns[thisPatternIndex];
    }
    #ifdef DEBUG
    Serial.println();
    #endif
    
    // pass temporary array to voice
    voiceSettings[v].selectPatterns(thesePatterns[0]);
  }  
}

uint8_t currentStepIndex = 0;

uint32_t lastStepInTicks = 0;
const uint32_t stepLengthInTicks = 500;

uint32_t lastPatternChangeInTicks = 0;
const uint32_t timeoutInTicks = 1000;

void loop() {
  
  // while waiting for next step..
  while (millis() < lastStepInTicks + stepLengthInTicks) {
      // give time to everything that needs it
      SwitchReader::giveTime();
      Triggers::giveTime();
  }
  lastStepInTicks = millis();
  
  #ifdef DEBUG
  Serial.print("Step "); Serial.println(currentStepIndex);
  Serial.println("--------------------");
  #endif
  
  // handle pattern change of all voices
  for (uint8_t voiceIndex = 0; voiceIndex < numbVoices; voiceIndex++) {
    
    // check if pattern for this voice has changed
    if (SwitchReader::hasSwitchMoved(voiceIndex)) {
      uint8_t newSwitchPosition = SwitchReader::getPosition(voiceIndex);
      #ifdef DEBUG
      Serial.print("Switch "); Serial.print(voiceIndex); Serial.print(" changed to "); Serial.println(newSwitchPosition);
      #endif
      
      // set the new pattern
      voiceSettings[voiceIndex].setActivePatternByIndex(newSwitchPosition);
      voiceSettings[voiceIndex].setMute(false);      

      // update time of last pattern change to avoid timeout
      lastPatternChangeInTicks = millis();

    // when pattern did not change..
    } else {
      
      // ..check for timeout
      if (millis() > lastPatternChangeInTicks + timeoutInTicks) {

        #ifdef DEBUG
        Serial.println("Timeout. Muting all voices");
        #endif
        
        // mute all voices    
        for (uint8_t voiceIndex = 0; voiceIndex < numbVoices; voiceIndex++) {
          voiceSettings[voiceIndex].setMute(true);
        }
      }      
    }    
  }
  
  // evaluate steps of all voices
  for (uint8_t voiceIndex = 0; voiceIndex < numbVoices; voiceIndex++) {
    PatternStep_t thisStep = voiceSettings[voiceIndex].evaluateStep(currentStepIndex);
    if (thisStep != OffStep) {
      #ifdef DEBUG
      Serial.print(voiceIndex); Serial.print(" ");
      #endif
      //fire trigger manager for the voice's channel
      Triggers::trigger(voiceSettings[voiceIndex].getOutputChannel());
    }
   }
   #ifdef DEBUG
   Serial.println();
   #endif
   
  // proceed to next Step
  currentStepIndex++;
  if (currentStepIndex == numbStepsPerPattern) currentStepIndex = 0;  
  
}
