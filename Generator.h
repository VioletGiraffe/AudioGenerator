#pragma once

#include "FixedPoint.h"

#include <cstdint>

using Fp10bits = FixedPoint<uint32_t, 10>;

class CGenerator
{
public:
	template <class Waveform, uint32_t samplingRate>
	uint16_t nextSample(uint16_t frequency /* Hz */)
	{
		const Fp10bits increment = frequency * Waveform::numSamples() / samplingRate; // 24000 / 600 * 25 = 1 kHz
		if (_phaseAccumulator < Waveform::numSamples() - increment.toInt())
			_phaseAccumulator += increment;

		return Waveform::sample(_phaseAccumulator.toInt());
	}

private:
	Fp10bits _phaseAccumulator = 0ul;
};

