#include <Arduino_NoMinMax.h>

#include "QuadratureRotaryEncoder.h"

volatile bool QuadratureRotaryEncoder::_event = false;
volatile int QuadratureRotaryEncoder::_counterVariable = 0;
Rotary QuadratureRotaryEncoder::_rotary;