#include <Arduino_NoMinMax.h>

#include "QuadratureRotaryEncoder.h"

QuadratureRotaryEncoder::QuadratureRotaryEncoder(int pinA, int pinB)
{
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);

	_debouncerA.attach(pinA);
	_debouncerA.interval(4);

	_debouncerB.attach(pinB);
	_debouncerB.interval(4);
}