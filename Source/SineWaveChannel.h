#pragma once
#include <cmath>
#include <cassert>
#include <juce_audio_basics/juce_audio_basics.h>

class SineWaveChannel
{
public:
    void prepare(double sampleRate); // no more channel dependency
    void process(float* output, int numSamples); // output pointer instead of buffer

    float getAmplitude() const { return amplitude; }
    float getFrequency() { return smoothedFrequency.getNextValue();}
    void setAmplitude(const float newAmplitude) { amplitude = newAmplitude; }
    void setFrequency(const float newFrequency) { smoothedFrequency.setTargetValue(newFrequency); }

private:
    float phase = 0.0f;
    float amplitude = 0.2f;
    float currentSampleRate = 0.0f;
    
    static constexpr float doublePi = 2.0f * juce::MathConstants<float>::pi;

    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFrequency;
};