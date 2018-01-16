/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "InstrumentGUIComponent.h"


//==============================================================================
/**
*/
class CustomPercussionV2AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    CustomPercussionV2AudioProcessorEditor (CustomPercussionV2AudioProcessor&, AudioProcessorValueTreeState&);
    ~CustomPercussionV2AudioProcessorEditor();

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CustomPercussionV2AudioProcessor& processor;

	GUI_Params gp;

	InstrumentGUIComponent instrumentGUIComponent{ &gp };

	// Audio Parameter Value tree object
	AudioProcessorValueTreeState& valueTreeState;
	// Noise 1 Listeners
	ScopedPointer<SliderAttachment> noise1VolumeSliderAttachment;
	ScopedPointer<SliderAttachment> noise1AttackSliderAttachment;
	ScopedPointer<SliderAttachment> noise1HoldSliderAttachment;
	ScopedPointer<SliderAttachment> noise1FadeSliderAttachment;
	// Noise 2 Listeners
	ScopedPointer<SliderAttachment> noise2VolumeSliderAttachment;
	ScopedPointer<SliderAttachment> noise2AttackSliderAttachment;
	ScopedPointer<SliderAttachment> noise2HoldSliderAttachment;
	ScopedPointer<SliderAttachment> noise2FadeSliderAttachment;
	// Oscillator Listeners
	ScopedPointer<SliderAttachment> oscVolumeSliderAttachment;
	ScopedPointer<SliderAttachment> oscPitchSliderAttachment;
	ScopedPointer<SliderAttachment> oscWaveFormSliderAttachment;
	ScopedPointer<SliderAttachment> oscAttackSliderAttachment;
	ScopedPointer<SliderAttachment> oscHoldSliderAttachment;
	ScopedPointer<SliderAttachment> oscFadeSliderAttachment;
	// Delay Listeners
	ScopedPointer<SliderAttachment> delay1VolumeSliderAttachment;
	ScopedPointer<SliderAttachment> delay1DelaySliderAttachment;
	ScopedPointer<SliderAttachment> delay2VolumeSliderAttachment;
	ScopedPointer<SliderAttachment> delay2DelaySliderAttachment;
	ScopedPointer<SliderAttachment> delay3VolumeSliderAttachment;
	ScopedPointer<SliderAttachment> delay3DelaySliderAttachment;
	ScopedPointer<SliderAttachment> delay4VolumeSliderAttachment;
	ScopedPointer<SliderAttachment> delay4DelaySliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomPercussionV2AudioProcessorEditor)
};
