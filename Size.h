#pragma once

#include <stdint.h>

class Size
{
public:
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
	inline uint16_t x() const {
		return _x;
	}

	inline uint16_t y() const {
		return _y;
	}

private:
	uint16_t _x = 0, _y = 0; // 16K resolution ought to be enough for anybody
};