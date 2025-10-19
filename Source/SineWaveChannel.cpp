#include "SineWaveChannel.h"

void SineWaveChannel::prepare(const double sampleRate)
{
	currentSampleRate = static_cast<float>(sampleRate);
	phase = 0.0f;
	smoothedFrequency.reset(currentSampleRate, 0.05f); // 50 ms frequency glide time
	smoothedFrequency.setCurrentAndTargetValue(getFrequency());
}

void SineWaveChannel::process(float* output, const int numSamples)
{
	assert(currentSampleRate > 0.0f);
	assert(amplitude >= 0.0f && amplitude <= 1.0f);

	for (int sample = 0; sample < numSamples; sample++)
	{
		const float frequency = smoothedFrequency.getNextValue();
		const float phaseIncrement = (doublePi * frequency) / currentSampleRate;
		output[sample] = amplitude * std::sinf(phase);
		phase += phaseIncrement;

		if (phase >= doublePi)
			phase -= doublePi;
	}
}
