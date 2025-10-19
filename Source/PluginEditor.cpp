#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SineWaveOscillatorAudioProcessorEditor::SineWaveOscillatorAudioProcessorEditor(SineWaveOscillatorAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p), frequencySliderAttachment (processorRef.parameters, "frequency", frequencySlider),
    playButtonAttachment (processorRef.parameters, "play", playButton)
{
    juce::ignoreUnused(processorRef);

    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    frequencySlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(frequencySlider);

    frequencyLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    frequencyLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(frequencyLabel);

    playButton.setButtonText("Playing");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    playButton.setClickingTogglesState(true);

    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);

    playButton.onClick = [this]()
        {
            // change the state of the button
            const bool isPlaying = playButton.getToggleState();
            playButton.setButtonText(isPlaying ? "Playing" : "Bypassed");
        };

    addAndMakeVisible(playButton);

    setSize (300, 400);
}

SineWaveOscillatorAudioProcessorEditor::~SineWaveOscillatorAudioProcessorEditor()
{
}

//==============================================================================
void SineWaveOscillatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("by aemulee", getLocalBounds(), juce::Justification::bottomRight, 1);
}

void SineWaveOscillatorAudioProcessorEditor::resized()
{
    frequencyLabel.setBounds(getWidth() / 2 - 60, getHeight() / 2 - 120, 120, 20);
    frequencySlider.setBounds(getWidth() / 2 - 60, getHeight() / 2 - 100, 120, 200);
    playButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 + 120, 100, 20);
}
