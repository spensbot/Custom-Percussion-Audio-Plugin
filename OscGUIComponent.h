/*
  ==============================================================================

    OscGUI.h
    Created: 17 Dec 2017 7:57:39am
    Author:  spens

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiParams.h"

class OscGUIComponent : public Component
{
public:
	OscGUIComponent()
	{
		//You can't run anything here that relies on the GUI_Params object.
	}

	void setParams(GUI_Params* gp_) {
		gp = gp_;
		height = gp->oscHeight;
		width = (gp->width / 2) - (1.5 * gp->padding);

		int currentY = gp->componentTitleHeight;

		addAndMakeVisible(volumeSlider);
		gp->addHorizontalSlider(&volumeSlider, &currentY);

		addAndMakeVisible(pitchSlider);
		gp->addHorizontalSlider(&pitchSlider, &currentY);

		addAndMakeVisible(waveFormSlider);
		gp->addHorizontalSlider(&waveFormSlider, &currentY);

		int ahfSliderWidth = (width - gp->labelWidth) / 3;
		for (int i = 0; i < 3; i++) {
			addAndMakeVisible(ahfSliders[i]);
			ahfSliders[i].setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
			ahfSliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 60, 20);
			ahfSliders[i].setBounds(gp->labelWidth + ahfSliderWidth * i, currentY, ahfSliderWidth, gp->rotarySliderHeight);
		}
	}

	void paint(Graphics& g) {
		gp->createComponentBackground(g, height, width, componentTitle);

		gp->drawLabels(g, labels, labelTypes, 4);
	};

	void resized() {};

	Slider volumeSlider;
	Slider pitchSlider;
	Slider waveFormSlider;
	Slider ahfSliders[3];

private:

	GUI_Params* gp = nullptr;
	int height;
	int width;
	char* componentTitle = "Oscillator";

	char* labels[4] = { "Volume", "Pitch", "WaveForm", "Envelope" };
	int labelTypes[4] = { 0, 0, 0, 1 };
};
