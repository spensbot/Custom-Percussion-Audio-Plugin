/*
  ==============================================================================

    GuiParams.h
    Created: 17 Dec 2017 10:52:47am
    Author:  spens

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class GUI_Params
{
public:

	GUI_Params() {
		height = titleHeight + oscHeight + delayHeight + thumbnailHeight + padding * 3;
		oscY = titleHeight;
		delayY = oscY + oscHeight + padding;
		thumbnailY = delayY + delayHeight + padding;
	}

	void createComponentBackground(Graphics& g, int height_, int width_, char* title_) {
		//Set background
		g.setColour(colour_ComponentBackGround);
		g.fillRoundedRectangle(0.0f, 0.0f, width_, height_, padding);

		//Set title background
		g.setColour(colour_ComponentTitleBackGround);
		g.fillRoundedRectangle(0.0f, 0.0f, width_, componentTitleHeight, padding);

		//Draw title text
		g.setColour(colour_ComponentText);
		g.setFont(font2);
		g.drawText(title_, padding, 0, width_, componentTitleHeight, Justification::centredLeft);
	}

	void drawLabels(Graphics& g, char** labels, int* labelTypes, int numElements) {

		g.setColour(colour_ComponentText);
		g.setFont(font3);

		int currentY = componentTitleHeight;
		int currentLabelHeight;

		for (int i = 0; i < numElements; i++) {

			switch (labelTypes[i]) {
			case 0: currentLabelHeight = horizontalSliderHeight;
				break;
			case 1: currentLabelHeight = rotarySliderHeight;
				break;
			}
			
			g.drawText(labels[i], padding, currentY, labelWidth, currentLabelHeight, juce::Justification::centredLeft);

			currentY += currentLabelHeight;
		}
	}

	void addHorizontalSlider(Slider* slider, int* currentY) {
		slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 60, 20);
		slider->setBounds(labelWidth, *currentY, width/2 - padding*3 - labelWidth, horizontalSliderHeight);
		*currentY += horizontalSliderHeight;
	}

//==========================    Object Declarations =================================================================

	Font font1 = Font("Lovelo Line", 60.0f, Font::plain);
	Font font2 = Font("Caviar Dreams", 30.0f, Font::bold);
	Font font3 = Font("Caviar Dreams", 20.0f, Font::plain);

	Colour colour_ComponentBackGround = Colours::darkcyan;
	Colour colour_ComponentTitleBackGround = Colours::cadetblue;
	Colour colour_ComponentText = Colours::antiquewhite;

	int width = 600;
	int height;

	int oscY;
	int delayY;
	int thumbnailY;

	int titleHeight = 60;
	int oscHeight = 250;
	int delayHeight = 200;
	int thumbnailHeight = 100;

	int componentTitleHeight = 30;
	int labelWidth = 80;
	int horizontalSliderHeight = 30;
	int rotarySliderHeight = 50;

	int padding = 5;

private:

} ;