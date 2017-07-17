#ifndef __GUARD_SETTINGS
#define __GUARD_SETTINGS

#include "pattern.h"
#include "VoiceSettings.h"

// total number of voices
// not a tweakable constant
const uint8_t numbVoices = 6;

// list of all patterns that can be used inside voices
static Pattern_t Patterns[numbPatterns] = {
  /*  0 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  1 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  2 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  3 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  4 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  5 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  6 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  7 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  8 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  9 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /* 10 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /* 11 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
};

// each voice can use a few of the above patterns
// select them by their indices
uint8_t patternsPerVoice[numbVoices][VoiceSettings_t::numbPatternsPerVoice] = {
  { 0, 1, 2, 3, 4, 5 },
  { 0, 1, 2, 3, 4, 5 },
  { 0, 1, 2, 3, 4, 5 },
  { 0, 1, 2, 3, 4, 5 },
  { 0, 1, 2, 3, 4, 5 },
  { 0, 1, 2, 3, 4, 5 },
};



#endif
