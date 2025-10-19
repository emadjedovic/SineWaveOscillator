#pragma once
#include <cmath>

class SineWaveChannel
{
public:
    void prepare(double sampleRate); // no more channel dependency
    void process(float* output, int numSamples); // output pointer instead of buffer
    float getAmplitude() const { return amplitude; }
    float getFrequency() const { return frequency; }
    void setAmplitude(const float newAmplitude) { amplitude = newAmplitude; }
    void setFrequency(const float newFrequency) { frequency = newFrequency; }

private:
    float amplitude = 0.2f;
    float frequency = 440.0f;
    float currentSampleRate = 0.0f;
    float timeIncrement = 0.0f;
    float currentTime = 0.0f;
    static constexpr float pi_f = 3.14159265358979323846f;
};