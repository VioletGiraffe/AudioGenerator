#include "waveformgenerator.h"

WaveformGenerator::~WaveformGenerator()
{
}

float WaveformGenerator::extraParameter() const
{
	return _extraParameter;
}

bool WaveformGenerator::hasExtraParameter() const
{
	return false;
}

const WaveformGenerator::ExtraParameterProperties WaveformGenerator::extraParameterProperties()
{
	return ExtraParameterProperties{std::string(), 0.0f, 0.0f, 0.0f};
}

void WaveformGenerator::setExtraParameter(float p)
{
	_extraParameter = p;
}
