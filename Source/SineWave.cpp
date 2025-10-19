#include "SineWave.h"

void SineWave::prepare(const double sampleRate, const int numChannels)
{
    currentSampleRate = static_cast<float>(sampleRate); // double to float
    phases.resize(numChannels, 0.0f);
    smoothedFreq.reset(currentSampleRate, 0.05f);
    smoothedFreq.setCurrentAndTargetValue(getFrequency());
}

void SineWave::process(juce::AudioBuffer<float>& buffer)
{
    assert(currentSampleRate > 0.0f);
    assert(amplitude >= 0.0f && amplitude <= 1.0f);
    assert(buffer.getNumChannels() == phases.size());

    // left speaker and right speaker (two channels)
    // create currentTime for each channel we are processing?
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);
        auto& phase = phases[channel];

        // for example, 512 samples in a block
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            const float frequency = smoothedFreq.getNextValue();
            const float phaseIncrement = (doublePi * frequency) / currentSampleRate;

            channelData[sample] = amplitude * std::sin(phase);
            phase += phaseIncrement;

            if (phase >= doublePi)
                phase -= doublePi;
        }
    }
}
