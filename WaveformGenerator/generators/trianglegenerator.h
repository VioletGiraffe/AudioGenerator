#pragma once

#include "../waveformgenerator.h"

class TriangleGenerator : public WaveformGenerator
{
public:
	TriangleGenerator();

	std::vector<float> generate(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false) override;
	const char* name() const override;

	bool hasExtraParameter() const override;
	const ExtraParameterProperties extraParameterProperties() override;
};
