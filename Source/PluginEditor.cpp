#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SineWaveOscillatorAudioProcessorEditor::SineWaveOscillatorAudioProcessorEditor(SineWaveOscillatorAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p), frequencySliderAttachment (processorRef.parameters, "frequency", frequencySlider)
{
    juce::ignoreUnused(processorRef);

    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(frequencySlider);

    // frequencyLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);
    frequencyLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(frequencyLabel);

    setSize (300, 400);
}

SineWaveOscillatorAudioProcessorEditor::~SineWaveOscillatorAudioProcessorEditor()
{
}

//==============================================================================
void SineWaveOscillatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::lightgrey);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("by aemulee", getLocalBounds(), juce::Justification::bottomRight, 1);
}

void SineWaveOscillatorAudioProcessorEditor::resized()
{
    frequencyLabel.setBounds(getWidth() / 2 - 60, getHeight() / 2 - 120, 120, 20);
    frequencySlider.setBounds(getWidth() / 2 - 60, getHeight() / 2 - 100, 120, 200);
}
