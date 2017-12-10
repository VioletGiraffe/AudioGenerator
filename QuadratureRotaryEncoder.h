#pragma once

#include "default_constructible_ref.hpp"

#include <Bounce2.h>

#include <functional>

class QuadratureRotaryEncoder
{
public:
	enum RotationDirection { CW, CCW };

	QuadratureRotaryEncoder(int pinA, int pinB, const default_constructible_ref<int>& value = default_constructible_ref<int>());

	inline void setOnRotationListener(const std::function<void(RotationDirection)>& listener) {
		_rotationListener = listener;
	}

	inline void setControlledValue(const default_constructible_ref<int>& value) {
		_value = value;
	}

	// Recommended update interval: 0.5 ms (2 kHz)
	void update();

private:
	Bounce _debouncerA, _debouncerB;
	std::function<void(RotationDirection)> _rotationListener = [](RotationDirection) {};
	default_constructible_ref<int> _value;
};
