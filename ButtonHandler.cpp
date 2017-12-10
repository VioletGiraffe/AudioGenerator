#include "ButtonHandler.h"

#include <Arduino.h>

constexpr uint32_t LONG_PRESS_TIME_MILLIS = 700u;
constexpr uint32_t DOUBLE_CLICK_TIME_MILLIS = 200u;

ButtonHandler::ButtonHandler(int buttonPin, NormalState normalState, ActiveLevel activeLevel) : _normalState(normalState), _activeLevel(activeLevel)
{
	pinMode(buttonPin, INPUT_PULLUP);

	_debouncer.attach(buttonPin);
	_debouncer.interval(20);
}

void ButtonHandler::update()
{
	_debouncer.update();

	const bool rose = _debouncer.rose();
	const bool fell = rose ? false : _debouncer.fell();

	if ((_activeLevel == ActiveLow && fell) || (_activeLevel == ActiveHigh && rose))
	{
		// Button activated
		_lastButtonPressTimeStamp = millis();
		_buttonPressListener();
	}
	else if ((_activeLevel == ActiveLow && rose) || (_activeLevel == ActiveHigh && fell))
	{
		// Button deactivated
		_longPressInvoked = false;

		_buttonReleaseListener();
		const auto timeStamp = millis();
		if (timeStamp - _lastButtonPressTimeStamp < LONG_PRESS_TIME_MILLIS)
		{
			_lastButtonClickTimestamp = timeStamp;
			_buttonClickListener();

			if (timeStamp - _lastButtonClickTimestamp < DOUBLE_CLICK_TIME_MILLIS)
			{
				_lastButtonClickTimestamp = 0;
				_buttonDoubleClickListener();
			}
		}
	}
	else if (!_longPressInvoked && ((_activeLevel == ActiveLow && _debouncer.read() == false) || (_activeLevel == ActiveHigh && _debouncer.read() == true)))
	{
		// Still pressed - check for long press
		const auto timeSincePressMillis = millis() - _lastButtonPressTimeStamp;
		if (timeSincePressMillis >= LONG_PRESS_TIME_MILLIS)
		{
			_longPressInvoked = true;
			_buttonLongPressListener();
		}
	}
}
