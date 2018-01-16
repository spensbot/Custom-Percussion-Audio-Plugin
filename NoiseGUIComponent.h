/*
  ==============================================================================

    NoiseGUI.h
    Created: 17 Dec 2017 7:57:15am
    Author:  spens

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiParams.h"

class NoiseGUIComponent : public Component
{
public:
	NoiseGUIComponent()
	{
		//You can't run anything here that relies on the GUI_Params object.
	}

	void setParams(GUI_Params* gp_) {
		gp = gp_;
		height = gp->oscHeight / 2 - gp->padding / 2;
		width = (gp->width / 2) - (1.5 * gp->padding);
		
		int currentY = 0;

		addAndMakeVisible(volumeSlider);
		volumeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 60, 20);
		volumeSlider.setBounds(gp->labelWidth, currentY += gp->componentTitleHeight, width - gp->labelWidth, gp->horizontalSliderHeight);

		int ahfSliderWidth = (width - gp->labelWidth) / 3;
		currentY += gp->horizontalSliderHeight;
		for (int i = 0; i < 3; i++) {
			addAndMakeVisible(ahfSliders[i]);
			ahfSliders[i].setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
			ahfSliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 60, 20);
			ahfSliders[i].setBounds(gp->labelWidth + ahfSliderWidth * i, currentY, ahfSliderWidth, gp->rotarySliderHeight);
		}
	}

	void paint(Graphics& g) {

		gp->createComponentBackground(g, height, width, componentTitle);

		gp->drawLabels(g, labels, labelTypes, 2);
	};

	void resized() {};

//************************ OBJECT DECLARATIONS ****************************
	char* componentTitle = "Noise";

	Slider volumeSlider;
	Slider ahfSliders[3];

private:

	GUI_Params* gp = nullptr;
	int height;
	int width;

	char* labels[2] = { "Volume", "Envelope" };
	int labelTypes[2] = { 0, 1 };
};
