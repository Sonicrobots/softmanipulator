#ifndef __GUARD_VOICE_SETTINGS
#define __GUARD_VOICE_SETTINGS

#include "pattern.h"

/* VoiceSettings
 * -------------
 * - storage for static settings of a voice (patterns)
 * - dynamic setting of output channel, active pattern and mute
 * - tiny bit of logic for getting the step value of active pattern
 *
 */

class VoiceSettings_t {
public:
  static const uint8_t numbPatternsPerVoice = 6;
public:
  void selectPatterns(Pattern_t* patterns);
  
  void setOutputChannel(uint8_t);
  uint8_t getOutputChannel();
  
  void setMute(bool);
  
  void setActivePatternByIndex(uint8_t);
  uint8_t getActivePatternIndex();
  
  PatternStep_t evaluateStep(uint8_t stepIndex);
  
private:
  Pattern_t * patterns[numbPatternsPerVoice];
  
  uint8_t outputChannel;
  bool muted;
 
  uint8_t activePatternIndex;
};

#endif
