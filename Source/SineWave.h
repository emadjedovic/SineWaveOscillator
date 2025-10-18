#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class SineWave
{
public:
    void prepare(double rate, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);

    float getAmplitude() const { return amplitude; }
    float getFrequency() const { return frequency; }
    void setAmplitude(const float newAmplitude) { amplitude = newAmplitude; }
    void setFrequence(const float newFrequency) { frequency = newFrequency; }

private:
    // keep track of time seperately for each channel of audio
    std::vector<float> currentTime;
    float frequency = 440.0f;
    float amplitude = 0.00f;
    float sampleRate = 0.0f;
    float timeIncrement = 0.0f;
    static constexpr float pi_f = 3.14159265358979323846f;
};