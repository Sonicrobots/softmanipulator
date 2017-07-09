#ifndef __GUARD_PATTERN
#define __GUARD_PATTERN

#include <inttypes.h>

const uint8_t numbStepsPerPattern = 4*8;
const uint8_t numbPatterns = 12;

typedef bool PatternStep_t;
typedef PatternStep_t Pattern_t[numbStepsPerPattern];
const PatternStep_t OffStep = false;

static Pattern_t Patterns[numbPatterns];

#endif
