#pragma once

#include "Size.h"

class Widget
{
public:
	Widget();

	inline Size size() const {
		return _size;
	}

	inline Point topLeft() const {
		return _topLeft;
	}

private:
	Size _size;
	Point _topLeft;
};
