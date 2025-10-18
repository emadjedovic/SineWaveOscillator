/*
  ==============================================================================

    SineWave.h
    Created: 18 Oct 2025 3:31:13pm
    Author:  Ema

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class SineWave
{
public:
    void prepare(double sampleRate, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float amplitude = 0.2f;
    float frequency = 440.0f;
    float currentSampleRate = 0.0f;
    float timeIncrement = 0.0f;

    std::vector<float> currentTime;
     
};