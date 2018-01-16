/*
  ==============================================================================

    InstrumentGUI.h
    Created: 17 Dec 2017 8:19:23am
    Author:  spens

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayGUIComponent.h"
#include "NoiseGUIComponent.h"
#include "OscGUIComponent.h"
#include "GuiParams.h"

class InstrumentGUIComponent : public Component
{
public:
	InstrumentGUIComponent(GUI_Params* gp_)
	{
		gp = gp_;

		delayComponent.setParams(gp);
		addAndMakeVisible(delayComponent);
		delayComponent.setBounds(gp->padding, gp->delayY, gp->width, gp->delayHeight);

		noiseComponent1.setParams(gp);
		noiseComponent1.componentTitle = "Noise 1";
		addAndMakeVisible(noiseComponent1);
		noiseComponent1.setBounds(gp->padding, gp->oscY, gp->width/2, gp->oscHeight/2);

		noiseComponent2.setParams(gp);
		noiseComponent2.componentTitle = "Noise 2";
		addAndMakeVisible(noiseComponent2);
		noiseComponent2.setBounds(gp->padding, gp->oscY + gp->oscHeight/2 + gp->padding/2, gp->width / 2, gp->oscHeight/2);

		oscComponent.setParams(gp);
		addAndMakeVisible(oscComponent);
		oscComponent.setBounds(gp->padding / 2 + gp->width / 2, gp->oscY, gp->width/2, gp->oscHeight);
	}

	void paint(Graphics& g) override{
		g.setColour(gp->colour_ComponentText);
		g.setFont(gp->font1);
		g.drawText("Custom Percussion", gp->padding, 0, gp->width, gp->titleHeight, Justification::centred);
	};

	DelayGUIComponent delayComponent;
	NoiseGUIComponent noiseComponent1;
	NoiseGUIComponent noiseComponent2;
	OscGUIComponent oscComponent;

private:
	GUI_Params* gp = nullptr;
};