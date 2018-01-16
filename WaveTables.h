/*
==============================================================================

WaveTables.h
Created: 4 Dec 2017 10:24:54am
Author:  spens

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Oscillator
{
public:

	Oscillator(int samplesPerTable_) : samplesPerTable(samplesPerTable_){

		sinWaveTable.setSize(1, samplesPerTable);
		squareWaveTable.setSize(1, samplesPerTable);
		sawWaveTable.setSize(1, samplesPerTable);

		sinData = sinWaveTable.getWritePointer(0);
		squareData = squareWaveTable.getWritePointer(0);
		sawData = sawWaveTable.getWritePointer(0);

		for (int sample = 0; sample < samplesPerTable; sample++) {

			//Calculate sin wave table
			sinData[sample] = float(std::sin((double(sample) / double(samplesPerTable)) * 2.0 * double_Pi));

			//Calculate square wave table
			if (sample < samplesPerTable / 2) {
				squareData[sample] = -0.25f;
			}
			else {
				squareData[sample] = 0.25f;
			}

			//Calculate saw wave table
			sawData[sample] = -0.25f + float(sample) / float(samplesPerTable) * 0.5f;
		}

		sinReadData = sinWaveTable.getReadPointer(0);
		squareReadData = squareWaveTable.getReadPointer(0);
		sawReadData = sawWaveTable.getReadPointer(0);
	}

	float getNextSample() {

		elapsedSamples++;

		int index = (samplesPerTable / int(std::round(samplesPerCycle))) * elapsedSamples % samplesPerTable;

		switch (waveShape) {
		case 1:
			return sinReadData[index];
		case 2:
			return squareReadData[index];
		case 3:
			return sawReadData[index];
		}
		return 0.0f;
	}

	void reset(double frequency_, double sampleRate_, int waveShape_) {
		frequency = frequency_;
		sampleRate = sampleRate_;
		waveShape = waveShape_;
		elapsedSamples = -1;
		samplesPerCycle = sampleRate / frequency;
	}

private:
	int samplesPerTable;
	int channelsPerTable;

	int waveShape;
	double frequency;
	int elapsedSamples;
	double sampleRate;
	double samplesPerCycle;

	float* sinData;
	float* squareData;
	float* sawData;

	const float* sinReadData;
	const float* squareReadData;
	const float* sawReadData;

	AudioSampleBuffer sinWaveTable;
	AudioSampleBuffer squareWaveTable;
	AudioSampleBuffer sawWaveTable;
};

class ADSR_envelope //Attack - Decay - Sustain - Release
{
public:

private:

};

class AHF_envelope //Attack - Hold - Fade
{
public:
	AHF_envelope() {

	}

	//Sets the sample rate of the enveloped sound, and reset the sample counter.
	void reset(double sampleRate_, double attack, double hold, double fade) {
		finished = false;
		elapsedSamples = -1;
		attackSamples = int(attack * sampleRate_);
		holdSamples = int(hold * sampleRate_);
		fadeSamples = int(fade * sampleRate_);
	}

	//Returns successive envelope samples.
	float getEnvelope() {

		elapsedSamples++;

		if (elapsedSamples < attackSamples) {
			return float(elapsedSamples) / float(attackSamples);
		}
		else if (elapsedSamples < (attackSamples + holdSamples)) {
			return 1.0f;
		}
		else if (elapsedSamples < attackSamples + holdSamples + fadeSamples) {
			return 1.0f - float(elapsedSamples - attackSamples - holdSamples) / float(fadeSamples);
		}
		else {
			finished = true;
			return 0.0f;
		}
	}

	//Use to check if the envelope has reached its end.
	bool isFinished() {
		return finished;
	}

private:
	int elapsedSamples;

	bool finished;

	int attackSamples;
	int holdSamples;
	int fadeSamples;
};

class AF_envelope {
public:
	//Sets the sample rate of the enveloped sound, and reset the sample counter.
	void reset(double sampleRate_, double attack, double fade) {
		finished = false;
		elapsedSamples = -1;
		attackSamples = int(attack * sampleRate_);
		fadeSamples = int(fade * sampleRate_);
	}

	//Returns successive envelope samples.
	float getEnvelope() {

		elapsedSamples++;

		if (elapsedSamples < attackSamples) {
			return float(elapsedSamples) / float(attackSamples);
		}
		else if (elapsedSamples < (attackSamples + fadeSamples)) {
			return 1.0f - float(elapsedSamples - attackSamples) / float(fadeSamples);
		}
		else {
			finished = true;
			return 0.0f;
		}
	}

	//Use to check if the envelope has reached its end.
	bool isFinished() {
		return finished;
	}

private:
	int elapsedSamples;
	int attackSamples;
	int fadeSamples;

	bool finished;
};

class NoiseGenerator {
public:
	
	float getNextSample() {
		return (random.nextFloat() - 0.5f) * .25;
	}

private:
	Random random;
};

class Noise_Generator_Frequency {
public:
	void reset(double frequency_, double sampleRate_) {
		frequency = frequency_;
		sampleRate = sampleRate_;
		samplesPerRandom = int(sampleRate / frequency);
		last = 0.0f;
		next = (random.nextFloat() - 0.5f) * 0.5f;
		step = -1;
	}

	float getNextSample() {

		step++;

		if (step == 0) {
			return last;
		}
		else if (step == samplesPerRandom) {
			last = next;
			next = (random.nextFloat() - 0.5f) * 0.5f;
			step = -1;
			return last;
		}
		else {
			return last + float(step / samplesPerRandom)*(next - last);
		}
	}

private:
	double sampleRate;
	double frequency;
	Random random;

	int samplesPerRandom;
	int step;

	float last;
	float next;
};