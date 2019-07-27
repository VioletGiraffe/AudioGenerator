#pragma once

#include <Bounce2.h>

class QuadratureRotaryEncoder
{
public:
	enum RotationDirection { CW, CCW };

	using RotationListener = void (*)(void* /*context */, RotationDirection);

	QuadratureRotaryEncoder(int pinA, int pinB);

	inline void setOnRotationListener(void* context, RotationListener listener)  noexcept {
		_rotationListener = listener;
		_listenerContext = context;
	}

	inline void setControlledValue(volatile int& counterVariable) noexcept {
		_counterVariable = &counterVariable;
	}

	// Recommended update interval: 0.5 ms (2 kHz)
	inline void update() noexcept {
		_debouncerA.update();
		_debouncerB.update();

		if (_debouncerA.fell())
		{
			const bool cw = _debouncerB.read();
			if (cw)
				++*_counterVariable;
			else
				--*_counterVariable;

			_rotationListener(_listenerContext, cw ? CW : CCW);
		}
	}

private:
	Bounce _debouncerA, _debouncerB;
	RotationListener _rotationListener;
	void* _listenerContext;

	volatile int* _counterVariable;
};
