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
    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);

private:
     
};