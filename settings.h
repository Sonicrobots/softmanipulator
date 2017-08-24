#ifndef __GUARD_SETTINGS
#define __GUARD_SETTINGS

#include "pattern.h"
#include "VoiceSettings.h"

// uncomment this to enable debug prints via Arduino's Serial at 115200
// this cannot be used together with SEND_MIDI functionality
#define DEBUG

// send a MIDI note together with every actuator hit
// this cannot be used together with DEBUG prints
//#define SEND_MIDI

// total number of voices
// not a tweakable constant
const uint8_t numbVoices = 4;

// list of all patterns that can be used inside voices
static Pattern_t Patterns[numbPatterns] = {
  /*  0 */ {OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep, OffStep},
  /*  1 */ {true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep, true, OffStep, OffStep, OffStep},
  /*  2 */ {true, OffStep, true,    OffStep, true, OffStep, true,    OffStep, true, OffStep, true,    OffStep, true, OffStep, true,    OffStep, true, OffStep, true,    OffStep, true, OffStep, true,    OffStep, true, OffStep, true,    OffStep, true, OffStep, true,    OffStep},
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
  { 0, 0, 0, 2, 2, 2 },
  { 2, 0, 2, 3, 4, 5 },
  { 0, 1, 2, 3, 4, 5 },
  //{ 0, 1, 2, 3, 4, 5 },
  //{ 0, 1, 2, 3, 4, 5 },
};

// turn-off timeout in minutes
const uint8_t timeoutInMinutes = 20;

// sequencer speed
const uint8_t beatsPerMinute = 120;

// midi notes that will be sent when a voice triggers
const uint8_t midiNotesPerVoice[numbVoices] = {
  48, 49, 50, 51
};

// midi channel to send on
const uint8_t midiChannel = 1;



#if defined(DEBUG) && defined(SEND_MIDI)
#error("You can either use debug prints or send midi notes but no both")
#endif


#endif // INCLUDE GUARD
