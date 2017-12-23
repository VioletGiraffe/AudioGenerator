#pragma once

#include "Size.h"

class Widget
{
public:
	struct Attributes {
		uint8_t frameWidth = 0;
	};

	Widget(const Point& topLeft = Point{0, 0}, const Size& size = Size{0, 0});

	inline const Attributes& attributes() const {
		return _attributes;
	}

	inline void setAttributes(const Attributes& attrs) {
		_attributes = attrs;
	}

	inline Point topLeft() const {
		return _topLeft;
	}

	inline Size size() const {
		return _size;
	}

private:
	Attributes _attributes;
	Point _topLeft;
	Size _size;
};
