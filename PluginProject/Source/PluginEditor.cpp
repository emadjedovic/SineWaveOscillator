/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginProjectAudioProcessorEditor::PluginProjectAudioProcessorEditor (PluginProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 600);
}

PluginProjectAudioProcessorEditor::~PluginProjectAudioProcessorEditor()
{
}

//==============================================================================
void PluginProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::lightgrey);
    g.setFont (juce::FontOptions (20.0f));
    g.drawFittedText ("Hello from aemulee!", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
