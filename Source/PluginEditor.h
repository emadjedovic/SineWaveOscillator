#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SineWaveOscillatorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SineWaveOscillatorAudioProcessorEditor (SineWaveOscillatorAudioProcessor&);
    ~SineWaveOscillatorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider frequencySlider;
    juce::TextButton playButton;
    juce::Label frequencyLabel{ "FrequencyLabel", "Frequency" };

    juce::AudioProcessorValueTreeState::SliderAttachment freqSliderAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment playButtonAttachment;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SineWaveOscillatorAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWaveOscillatorAudioProcessorEditor)
};
