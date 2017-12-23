#pragma once

#include "default_constructible_ref.hpp"

template <class Display>
class Painter
{
public:
	Painter(Display& display) : _display(display) {}

protected:
	Display & _display;
};

template <class Display, class ConcretePainter = Painter<Display>>
class PainterFabricTemplate
{
public:
	static void init(Display& display) {
		_display = display;
	}

	static ConcretePainter createPainter() {
		return ConcretePainter(_display);
	}

private:
	static default_constructible_ref<Display> _display;
};