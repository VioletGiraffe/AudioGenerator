#pragma once

#include "Rotary.h"

enum RotationDirection { CW, CCW };

class QuadratureRotaryEncoder
{
	static void PinB_ISR()
	{
		const auto valB = digitalRead(49);
		const auto valA = digitalRead(51);
		
		const auto result = _rotary.process(valA != 0, valB != 0);
		if (result == DIR_CW)
		{
			++_counterVariable;
			_event = true;
		}
		else if (result == DIR_CCW)
		{
			--_counterVariable;
			_event = true;
		}
	}

public:
	using RotationListener = void (*)(void* /*context */, RotationDirection);

	QuadratureRotaryEncoder(int PinA, int PinB) noexcept
	{
		pinMode(PinA, INPUT_PULLUP);
		pinMode(PinA, INPUT_PULLUP);

		attachInterrupt(PinA, PinB_ISR, FALLING);
		attachInterrupt(PinB, PinB_ISR, FALLING);
	}

	inline void setOnRotationListener(void* context, RotationListener listener)  noexcept {
		_rotationListener = listener;
		_listenerContext = context;
	}

	inline bool checkForEvent() noexcept {
		if (_event)
		{
			_event = false;
			return true;
		}

		return false;
	}

	inline int counterValue() const {
		return _counterVariable;
	}

private:
	static volatile bool _event;

	static Rotary _rotary;

	RotationListener _rotationListener;
	void* _listenerContext;

	static volatile int _counterVariable;
};
