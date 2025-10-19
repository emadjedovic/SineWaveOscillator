#include "SineWaveChannel.h"

void SineWaveChannel::prepare(const double sampleRate)
{
	currentSampleRate = static_cast<float>(sampleRate);
	timeIncrement = 1.0f / currentSampleRate;
}

void SineWaveChannel::process(float* output, const int numSamples)
{
	for (int sample = 0; sample < numSamples; sample++)
	{
		output[sample] = amplitude * std::sinf(doublePi *frequency * currentTime);
		currentTime += timeIncrement;
	}
}
