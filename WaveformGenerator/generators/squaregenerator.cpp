#include "squaregenerator.h"

SquareGenerator::SquareGenerator()
{
	_extraParameter = 50.0f;
}

std::vector<float> SquareGenerator::generate(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples(numSamples, signedSamples ? -amplitude : 0.0f);

	const float dutyCycle = _extraParameter * 0.01f; // percent to fraction
	for (uint32_t i = 0, n = static_cast<uint32_t>(numSamples * dutyCycle + 0.5f); i < n; ++i)
		samples[i] = signedSamples ? amplitude : amplitude * 2.0f;

	return samples;
}

const char* SquareGenerator::name() const
{
	return "Square";
}

bool SquareGenerator::hasExtraParameter() const
{
	return true;
}

const WaveformGenerator::ExtraParameterProperties SquareGenerator::extraParameterProperties()
{
	return ExtraParameterProperties{"Duty cycle", 1.0f, 99.0f, 1.0f};
}
