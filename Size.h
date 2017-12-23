#pragma once

#include <stdint.h>

class Size
{
public:
	inline explicit Size(uint16_t w = 0, uint16_t h = 0) : _w(w), _h(h) {}

	inline uint16_t width() const {
		return _w;
	}

	inline uint16_t height() const {
		return _h;
	}

private:
	uint16_t _w = 0, _h = 0; // 16K resolution ought to be enough for anybody
};


class Point
{
public:
	inline explicit Point(uint16_t x = 0, uint16_t y = 0) : _x(x), _y(y) {}

	inline uint16_t x() const {
		return _x;
	}

	inline uint16_t y() const {
		return _y;
	}

private:
	uint16_t _x = 0, _y = 0; // 16K resolution ought to be enough for anybody
};