#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <cassert>

class SineWave
{
public:
	void prepare(double sampleRate, int numChannels);
	void process(juce::AudioBuffer<float>& buffer);

	float getAmplitude() const { return amplitude; }
	float getFrequency() { return smoothedFreq.getNextValue(); }
	void setAmplitude(const float newAmplitude) { amplitude = newAmplitude; }
	void setFrequency(const float newFrequency) { smoothedFreq.setTargetValue(newFrequency); }

private:
	// keep track of phases for each channel of audio
	std::vector<float> phases;
	float amplitude = 0.00f;
	float currentSampleRate = 0.0f;

	static constexpr float doublePi = 2.0f * juce::MathConstants<float>::pi;

	juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFreq;
};