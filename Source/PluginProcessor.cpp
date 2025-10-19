#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SineWaveOscillatorAudioProcessor::SineWaveOscillatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	), parameters(*this, nullptr, "ParameterTree", createParameterLayout())
#endif
{
	parameters.addParameterListener("frequency", this);
}

SineWaveOscillatorAudioProcessor::~SineWaveOscillatorAudioProcessor()
{
	parameters.removeParameterListener("frequency", this);
}

//==============================================================================
const juce::String SineWaveOscillatorAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool SineWaveOscillatorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool SineWaveOscillatorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool SineWaveOscillatorAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double SineWaveOscillatorAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int SineWaveOscillatorAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int SineWaveOscillatorAudioProcessor::getCurrentProgram()
{
	return 0;
}

void SineWaveOscillatorAudioProcessor::setCurrentProgram(int index)
{
	juce::ignoreUnused(index);
}

const juce::String SineWaveOscillatorAudioProcessor::getProgramName(int index)
{
	juce::ignoreUnused(index);
	return {};
}

void SineWaveOscillatorAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
	juce::ignoreUnused(index, newName);
}

//==============================================================================
void SineWaveOscillatorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	juce::ignoreUnused(samplesPerBlock);
	sinewave.prepare(sampleRate, getTotalNumOutputChannels());
	/*
	sineWaves.resize(getTotalNumOutputChannels());
	for (auto& wave : sineWaves)
		wave.prepare(sampleRate);
		*/
}

void SineWaveOscillatorAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SineWaveOscillatorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void SineWaveOscillatorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ignoreUnused(midiMessages);

	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	sinewave.process(buffer);

	/*
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
		auto* channelData = buffer.getWritePointer(channel);
		*/


		/*
		for (int channel = 0; channel < buffer.getNumChannels(); channel++)
		{
			auto* output = buffer.getWritePointer(channel);
			sineWaves[channel].process(output, buffer.getNumSamples());
		}
		*/
}

//==============================================================================
bool SineWaveOscillatorAudioProcessor::hasEditor() const
{
	return true;
}

juce::AudioProcessorEditor* SineWaveOscillatorAudioProcessor::createEditor()
{
	return new SineWaveOscillatorAudioProcessorEditor(*this);
}

//==============================================================================
void SineWaveOscillatorAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	juce::ignoreUnused(destData);
}

void SineWaveOscillatorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SineWaveOscillatorAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SineWaveOscillatorAudioProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameterList;
	juce::NormalisableRange<float> frequencyRange{ 20.0f, 20000.0f, 0.1f, 0.5f };
	parameterList.push_back(std::make_unique<juce::AudioParameterFloat>("frequency", "Frequency", frequencyRange, 500.0f));

	return { parameterList.begin(), parameterList.end()
	};
}

void SineWaveOscillatorAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
	if (parameterID == "frequency")
	{
		sinewave.setFrequency(newValue);
	}
}





