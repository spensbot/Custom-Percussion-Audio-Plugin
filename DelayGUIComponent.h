/*
  ==============================================================================

    DelayGUI.h
    Created: 17 Dec 2017 7:59:21am
    Author:  spens

  ==============================================================================
*/

#pragma once
#include "GuiParams.h"

class DelayGUIComponent : public Component
{
public:

	DelayGUIComponent() {

	}

	void setParams(GUI_Params* gp_) {
		gp = gp_;
		height = gp->delayHeight;
		width = gp->width - 2 * gp->padding;

		sliderWidth = (width - gp->labelWidth) / 4;
		sliderHeight = (height - gp->componentTitleHeight) / 2;

		for (int i = 0; i < 4; i++) {
			addAndMakeVisible(delayLevels[i]);
			delayLevels[i].setBounds(gp->labelWidth + sliderWidth * i, gp->componentTitleHeight, sliderWidth, sliderHeight);
			delayLevels[i].setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
			delayLevels[i].setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 60, 20);

			addAndMakeVisible(delayTimes[i]);
			delayTimes[i].setBounds(gp->labelWidth + sliderWidth * i, sliderHeight + gp->componentTitleHeight, sliderWidth, sliderHeight);
			delayTimes[i].setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
			delayTimes[i].setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 60, 20);
		}
	}

	void paint(Graphics& g) override{
		gp->createComponentBackground(g, height, width, "Delay Component");

		gp->drawLabels(g, labels, labelTypes, 2);
	};

	void resized() {};

	GUI_Params* gp = nullptr;

	Slider delayTimes[4];
	Slider delayLevels[4];

private:
	char* labels[2] = { "Volume", "Delay" };
	int labelTypes[2] = { 1, 1 };

	int padding;
	int width;
	int height;
	int sliderWidth;
	int sliderHeight;
};