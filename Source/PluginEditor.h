#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SineWaveOscillatorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit SineWaveOscillatorAudioProcessorEditor (SineWaveOscillatorAudioProcessor&);
    ~SineWaveOscillatorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider frequencySlider;
    juce::Label frequencyLabel{ "Freq Label", "Frequency" };
    SineWaveOscillatorAudioProcessor& processorRef;

    juce::AudioProcessorValueTreeState::SliderAttachment frequencySliderAttachment;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWaveOscillatorAudioProcessorEditor)
};
