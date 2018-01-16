/*
==============================================================================

SynthVoice.h
Created: 30 Nov 2017 12:04:41pm
Author:  spens

==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveTables.h"

class SynthSound : public SynthesiserSound
{
public:
	bool appliesToNote(int midiNoteNumber) {
		return true;
	}
	bool appliesToChannel(int midiChannel) {
		return true;
	}
private:
};

class SynthVoice : public SynthesiserVoice
{
public:

	SynthVoice(AudioProcessorValueTreeState* parameters_) : parameters (parameters_){
		level = 0.0f;
		delayBufferSamples = maxDelayTime * 48000;
		delayBuffer.setSize(1, delayBufferSamples, false, true, false);
		delayBuffer.clear();
	}

	bool canPlaySound(SynthesiserSound* sound) override {
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override {
		level = velocity;
		currentSampleRate = getSampleRate();
		noise1Envelope.reset(getSampleRate(), *parameters->getRawParameterValue("noise1Attack"), *parameters->getRawParameterValue("noise1Hold"), *parameters->getRawParameterValue("noise1Fade"));
		noise2Envelope.reset(getSampleRate(), *parameters->getRawParameterValue("noise2Attack"), *parameters->getRawParameterValue("noise2Hold"), *parameters->getRawParameterValue("noise2Fade"));
		osc.reset(*parameters->getRawParameterValue("oscPitch") * 2000, getSampleRate(), 1);
		oscEnvelope.reset(getSampleRate(), *parameters->getRawParameterValue("oscAttack"), *parameters->getRawParameterValue("oscHold"), *parameters->getRawParameterValue("oscFade"));
		absoluteCurrentSample = 0;
	}

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {

		while (--numSamples >= 0) 
		{
			if (level > 0.0f) {
				// Noise 1 Contribution
				float currentSample = noise1.getNextSample() * noise1Envelope.getEnvelope() * *parameters->getRawParameterValue("noise1Volume");
				// Noise 2 Contribution
				currentSample += noise2.getNextSample() * noise2Envelope.getEnvelope() * *parameters->getRawParameterValue("noise2Volume");
				// Oscillator Contribution
				currentSample += osc.getNextSample() * oscEnvelope.getEnvelope() * *parameters->getRawParameterValue("oscVolume");
				currentSample *= level;
				
				// Create buffer with delay data
				delayBuffer.addSample(0, absoluteCurrentSample, currentSample);

				// Delay Contributions

				currentSample += addDelay(*parameters->getRawParameterValue("delay1Volume"), *parameters->getRawParameterValue("delay1Delay"));
				currentSample += addDelay(.5, .1);
				currentSample += addDelay(.5, .15);
				currentSample += addDelay(.5, .2);

				for (int channel = outputBuffer.getNumChannels(); --channel >= 0;) {
					outputBuffer.addSample(channel, startSample, currentSample);
				}
				
				if (noise1Envelope.isFinished()) {
					if (noise2Envelope.isFinished()) {
						if (oscEnvelope.isFinished()) {
							level = 0.0f;
							clearCurrentNote();
						}
					}
				}
				++absoluteCurrentSample;
			}
			++startSample;
		}
	}

	void stopNote(float velocity, bool allowTailOff) override {
		if (!allowTailOff) {
			clearCurrentNote();
			level = 0.0f;
		}
	}

	void pitchWheelMoved(int newPitchWheelValue) {
	}

	void controllerMoved(int controllerNumber, int newControllerValue) {
	}

	float addDelay(float delayVolume, float delayTime) {
		int delaySamples = absoluteCurrentSample - (int)(currentSampleRate * delayTime);
		if (delaySamples < 0) {
			return 0.0f;
		} else {
			return delayBuffer.getSample(0, delaySamples) * delayVolume;
		}
	}

//================================ PARAMETERS =========================================

	float maxDelayTime = 3.0f; //seconds

private:

	float level;
	int absoluteCurrentSample;
	int delayBufferSamples;
	float currentSampleRate;

	AudioProcessorValueTreeState* parameters;

	NoiseGenerator noise1;
	AHF_envelope noise1Envelope;

	NoiseGenerator noise2;
	AHF_envelope noise2Envelope;

	Oscillator osc{ 5000 };
	AHF_envelope oscEnvelope;

	AudioBuffer<float> delayBuffer;
};