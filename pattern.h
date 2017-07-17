#ifndef __GUARD_PATTERN
#define __GUARD_PATTERN

#include <inttypes.h>

const uint8_t numbStepsPerPattern = 4*8;
const uint8_t numbPatterns = 12;

// type of a single step
typedef bool PatternStep_t;

// the single step that does _not_ trigger
const PatternStep_t OffStep = false;

// a bunch of single steps together is a pattern
struct Pattern_t{
  PatternStep_t steps[numbStepsPerPattern];
};
  

#endif
