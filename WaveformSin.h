#pragma once

#include <cstddef>
#include <cstdint>

class CWaveformSin
{
public:
	static inline size_t numSamples()
	{
		return 600u;
	}

	static inline uint16_t sample(size_t index)
	{
		return wavetable[index];
	}

private:
	static const uint16_t wavetable[];
};

