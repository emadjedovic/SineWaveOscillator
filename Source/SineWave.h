#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <cassert>

class SineWave
{
public:
	void prepare(double rate, int numChannels);
	void process(juce::AudioBuffer<float>& buffer);

	float getAmplitude() const { return amplitude; }
	float getFrequency() { return frequency; }
	void setAmplitude(const float newAmplitude) { amplitude = newAmplitude; }
	void setFrequency(const float newFrequency) { frequency = newFrequency; }

private:
	// keep track of time seperately for each channel of audio
	std::vector<float> currentTime;
	float frequency = 440.0f;
	float amplitude = 0.02f;
	float sampleRate = 0.0f;
	float timeIncrement = 0.0f;

	static constexpr float doublePi = 2.0f * juce::MathConstants<float>::pi;
};