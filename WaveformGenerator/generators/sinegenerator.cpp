#include "sinegenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

std::vector<float> SineGenerator::generate(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples;
	samples.reserve(numSamples);

	const float step = M_PI * 2.0f / (float)numSamples;
	for (uint32_t i = 0; i < numSamples; ++i)
	{
		float sample = amplitude * sin(i * step - M_PI_2);
		if (!signedSamples)
			sample += amplitude;

		samples.push_back(sample);
	}

	return samples;
}

const char* SineGenerator::name() const
{
	return "Sine";
}
