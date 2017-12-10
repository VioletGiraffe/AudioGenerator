#pragma once

#include <cstdint>
#include <string>
#include <vector>

class WaveformGenerator
{
public:
	virtual ~WaveformGenerator();

	virtual std::vector<float> generate(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false) = 0;
	virtual const char* name() const = 0;

	struct ExtraParameterProperties {
		std::string name;
		float minValue;
		float maxValue;
		float step;
	};

	virtual bool hasExtraParameter() const;
	virtual const ExtraParameterProperties extraParameterProperties();

	float extraParameter() const;
	void setExtraParameter(float p);

protected:
	float _extraParameter = 0.1f;
};
