#include "QuadratureRotaryEncoder.h"

#include <Arduino.h>

namespace std {
	// Dirty, dirty hack to work around bits and pieces missing from the Arduino standard library implementation
	void __throw_bad_function_call() {
		abort(); // To avoid "Noreturn function does return"
	}
}

QuadratureRotaryEncoder::QuadratureRotaryEncoder(int pinA, int pinB, const default_constructible_ref<int>& value) :
	_value(value)
{
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);

	_debouncerA.attach(pinA);
	_debouncerA.interval(4);

	_debouncerB.attach(pinB);
	_debouncerB.interval(4);
}

void QuadratureRotaryEncoder::update()
{
	_debouncerA.update();
	_debouncerB.update();

	if (_debouncerA.fell())
	{
		const bool cw = _debouncerB.read() != false;
		if (_value)
		{
			if (cw)
				++_value.get();
			else
				--_value.get();
		}

		_listener(cw ? CW : CCW);
	}
}
