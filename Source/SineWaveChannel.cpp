#include "SineWaveChannel.h"

void SineWaveChannel::prepare(double sampleRate)
{
	currentSampleRate = static_cast<float>(sampleRate);
	timeIncrement = 1.0f / currentSampleRate;
}

void SineWaveChannel::process(float* output, int numSamples)
{
	for (int sample = 0; sample < numSamples; sample++)
	{
		output[sample] = amplitude * std::sinf(2.0f * pi_f *frequency * currentTime);
		currentTime += timeIncrement;
	}
}
