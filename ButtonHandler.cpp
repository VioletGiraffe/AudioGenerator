#include <Arduino_NoMinMax.h>

#include "ButtonHandler.h"

constexpr uint32_t LONG_PRESS_TIME_MILLIS = 700u;
constexpr uint32_t DOUBLE_CLICK_TIME_MILLIS = 200u;

ButtonHandler::ButtonHandler(int buttonPin, NormalState normalState) : _normalState(normalState)
{
	pinMode(buttonPin, INPUT_PULLUP);

	_debouncer.attach(buttonPin);
	_debouncer.interval(4);
}

void ButtonHandler::update()
{
	_debouncer.update();

	const bool rose = _debouncer.rose();
	const bool fell = rose ? false : _debouncer.fell();

	if (fell)
	{
		// Button activated
		_lastButtonPressTimeStamp = millis();
		_buttonPressListener();
	}
	else if (rose)
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
		else
			_lastButtonPressTimeStamp = 0;
	}
	else if (!_longPressInvoked && _debouncer.read() == false)
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
