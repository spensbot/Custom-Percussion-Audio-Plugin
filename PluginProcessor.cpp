/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CustomPercussionV2AudioProcessor::CustomPercussionV2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : parameters(*this, nullptr), AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	// Noise 1 Parameters
	parameters.createAndAddParameter("noise1Volume", "Noise1Volume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, nullptr, nullptr);
	parameters.createAndAddParameter("noise1Attack", "Noise1Attack", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("noise1Hold", "Noise1Hold", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("noise1Fade", "Noise1Fade", String(), NormalisableRange<float>(0.0f, 1.0f), 0.1f, nullptr, nullptr);
	// Noise 2 Parameters
	parameters.createAndAddParameter("noise2Volume", "Noise2Volume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("noise2Attack", "Noise2Attack", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("noise2Hold", "Noise2Hold", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("noise2Fade", "Noise2Fade", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	// Oscillator Parameters
	parameters.createAndAddParameter("oscVolume", "OscVolume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("oscPitch", "OscPitch", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("oscWaveForm", "OscWaveForm", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("oscAttack", "OscAttack", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("oscHold", "OscHold", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("oscFade", "OscFade", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	// Delay Parameters
	parameters.createAndAddParameter("delay1Volume", "Delay1Volume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay2Volume", "Delay2Volume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay3Volume", "Delay3Volume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay4Volume", "Delay4Volume", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay1Delay", "Delay1Delay", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay2Delay", "Delay2Delay", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay3Delay", "Delay3Delay", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("delay4Delay", "Delay4sDelay", String(), NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);

	parameters.state = ValueTree(Identifier("CustomPercussion"));

	initialiseSynth(4);
}

CustomPercussionV2AudioProcessor::~CustomPercussionV2AudioProcessor()
{
}

void CustomPercussionV2AudioProcessor::initialiseSynth(const int numVoices)
{
	// Add some voices...
	for (int i = numVoices; --i >= 0;)
		mySynth.addVoice(new SynthVoice(&parameters));

	// ..and give the synth a sound to play
	mySynth.addSound(new SynthSound());
}

//==============================================================================
const String CustomPercussionV2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CustomPercussionV2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CustomPercussionV2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CustomPercussionV2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CustomPercussionV2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CustomPercussionV2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CustomPercussionV2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void CustomPercussionV2AudioProcessor::setCurrentProgram (int index)
{
}

const String CustomPercussionV2AudioProcessor::getProgramName (int index)
{
    return {};
}

void CustomPercussionV2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CustomPercussionV2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	mySynth.setCurrentPlaybackSampleRate(sampleRate);
}

void CustomPercussionV2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CustomPercussionV2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void CustomPercussionV2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	const int numSamples = buffer.getNumSamples();

	buffer.clear();

	mySynth.renderNextBlock(buffer, midiMessages, 0, numSamples);
}

//==============================================================================
bool CustomPercussionV2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CustomPercussionV2AudioProcessor::createEditor()
{
    return new CustomPercussionV2AudioProcessorEditor (*this, parameters);
}

//==============================================================================
void CustomPercussionV2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
	ScopedPointer<XmlElement> xml(parameters.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void CustomPercussionV2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.state = ValueTree::fromXml(*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CustomPercussionV2AudioProcessor();
}
