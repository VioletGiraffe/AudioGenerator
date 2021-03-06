#pragma once

#include "../waveformgenerator.h"

class SineGenerator : public WaveformGenerator
{
public:
	std::vector<float> generate(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false) override;
	const char* name() const override;
};
