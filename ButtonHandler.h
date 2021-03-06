#pragma once

#include <Bounce2.h>

#include <functional>

// The class is designed for active low level and pullup input
class ButtonHandler
{
public:
	enum NormalState {NormalOpen, NormalClosed};
	explicit ButtonHandler(int buttonPin, NormalState normalState = NormalOpen);

	inline void setButtonClickListener(const std::function<void()>& listener) {
		_buttonClickListener = listener;
	}

	inline void setButtonLongPressListener(const std::function<void()>& listener) {
		_buttonLongPressListener = listener;
	}

	inline void setButtonDoubleClickListener(const std::function<void()>& listener) {
		_buttonDoubleClickListener = listener;
	}

	inline void setButtonPressListener(const std::function<void()>& listener) {
		_buttonPressListener = listener;
	}

	inline void setButtonReleaseListener(const std::function<void()>& listener) {
		_buttonReleaseListener = listener;
	}

	// Recommended update interval: 0.5 ms (2 kHz)
	void update();

private:
	Bounce _debouncer;
	std::function<void()> _buttonClickListener = [](){};
	std::function<void()> _buttonLongPressListener = [](){};
	std::function<void()> _buttonDoubleClickListener = [](){};
	std::function<void()> _buttonPressListener = [](){};
	std::function<void()> _buttonReleaseListener = [](){};

	const NormalState _normalState;

	uint32_t _lastButtonPressTimeStamp, _lastButtonClickTimestamp = 0;
	bool _longPressInvoked = false;
};

