#pragma once

#include <stddef.h>
#include <stdint.h>

class CWaveformSin
{
public:
	static constexpr size_t numSamples = 512;

	static inline uint32_t sample(size_t index)
	{
		return wavetable[index];
	}

	static inline constexpr auto bufferAddress()
	{
		return wavetable;
	}

private:
	static uint32_t wavetable[numSamples];
};

