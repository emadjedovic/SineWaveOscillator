/*
  ==============================================================================

    SineWave.cpp
    Created: 18 Oct 2025 3:31:13pm
    Author:  Ema

  ==============================================================================
*/

#include "SineWave.h"

void SineWave::prepare(double sampleRate, int numChannels)
{
    currentSampleRate = static_cast<float>(sampleRate); // double to float
    // time increment is dependent on sample rate
    timeIncrement = 1.0f / currentSampleRate;
    currentTime.resize(numChannels, 0.0f);
}

void SineWave::process(juce::AudioBuffer<float>& buffer)
{
    if (currentTime.size() != buffer.getNumChannels()) return;

    // left speaker and right speaker (two channels)
    // create currentTime for each channel we are processing?
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* output = buffer.getWritePointer(channel);

        // for example, 512 samples in a block
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            output[sample] = amplitude * std::sinf(juce::MathConstants<float>::twoPi * frequency * currentTime[channel]);
            currentTime[channel] += timeIncrement;
        }
    }
}
