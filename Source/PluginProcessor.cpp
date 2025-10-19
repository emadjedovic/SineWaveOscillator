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
	), state(*this, nullptr, "parameters", createParameters())
#endif
{
}

SineWaveOscillatorAudioProcessor::~SineWaveOscillatorAudioProcessor()
{
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

	// returns std::atomic<float>*
	frequencyParam = state.getRawParameterValue("freqHz");
	// float shouldBePlaying = state.getRawParameterValue("play")->load(); // cast to bool?
	playParam = state.getRawParameterValue("play");
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

	const float freq = frequencyParam->load();
	const bool shouldBePlaying = static_cast<bool>(playParam->load());

	sinewave.setFrequency(freq);
	sinewave.setAmplitude(shouldBePlaying ? 0.4f : 0.0f);

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


juce::AudioProcessorValueTreeState::ParameterLayout SineWaveOscillatorAudioProcessor::createParameters()
{
	return {
		std::make_unique<juce::AudioParameterFloat>(
			juce::ParameterID{"freqHz"},
			"Frequency",
			20.0f,
			20000.0f,
			220.0f
		),
			std::make_unique<juce::AudioParameterBool>(
			juce::ParameterID{"play"},
			"Play",
			true
		)
	};
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SineWaveOscillatorAudioProcessor();
}

