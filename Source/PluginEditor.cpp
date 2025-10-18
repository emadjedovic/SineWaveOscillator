#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SineWaveOscillatorAudioProcessorEditor::SineWaveOscillatorAudioProcessorEditor(SineWaveOscillatorAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    frequencySlider.setRange(0.0f, 1.0f, 0.01f);
    addAndMakeVisible(frequencySlider);

    playButton.setButtonText("Playing");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    playButton.setClickingTogglesState(true);

    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);

    playButton.onClick = [this]()
        {
            // change the state of the button when it's clicked
            const bool isPlaying = playButton.getToggleState();
            playButton.setButtonText(isPlaying ? "Playing" : "Bypassed");
        };

    addAndMakeVisible(playButton);

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
    playButton.setBounds(getWidth() / 2 - 60, getHeight() / 2 + 120, 120, 20);
}
