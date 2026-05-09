#include "MicroStepDriver.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

static const uint8 negEnablePin=3;
static const uint8 posEnablePin=2;
static const uint8 negDirrectionPin=4;
static const uint8 posDirrectionPin=3;
static const uint8 negPulsePin=3;
static const uint8 posPulsePin=3;