/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CustomPercussionV2AudioProcessorEditor::CustomPercussionV2AudioProcessorEditor (CustomPercussionV2AudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (gp.width, gp.height);
	addAndMakeVisible(instrumentGUIComponent);
	instrumentGUIComponent.setBounds(0, 0, gp.width, gp.height);

	// Noise 1 Slider Attachments
	noise1VolumeSliderAttachment = new SliderAttachment(valueTreeState, "noise1Volume", instrumentGUIComponent.noiseComponent1.volumeSlider);
	noise1AttackSliderAttachment = new SliderAttachment(valueTreeState, "noise1Attack", instrumentGUIComponent.noiseComponent1.ahfSliders[0]);
	noise1HoldSliderAttachment = new SliderAttachment(valueTreeState, "noise1Hold", instrumentGUIComponent.noiseComponent1.ahfSliders[1]);
	noise1FadeSliderAttachment = new SliderAttachment(valueTreeState, "noise1Fade", instrumentGUIComponent.noiseComponent1.ahfSliders[2]);
	// Noise 2 Slider Attachments
	noise2VolumeSliderAttachment = new SliderAttachment(valueTreeState, "noise2Volume", instrumentGUIComponent.noiseComponent2.volumeSlider);
	noise2AttackSliderAttachment = new SliderAttachment(valueTreeState, "noise2Attack", instrumentGUIComponent.noiseComponent2.ahfSliders[0]);
	noise2HoldSliderAttachment = new SliderAttachment(valueTreeState, "noise2Hold", instrumentGUIComponent.noiseComponent2.ahfSliders[1]);
	noise2FadeSliderAttachment = new SliderAttachment(valueTreeState, "noise2Fade", instrumentGUIComponent.noiseComponent2.ahfSliders[2]);
	// Oscillator Slider Attachments
	oscVolumeSliderAttachment = new SliderAttachment(valueTreeState, "oscVolume", instrumentGUIComponent.oscComponent.volumeSlider);
	oscPitchSliderAttachment = new SliderAttachment(valueTreeState, "oscPitch", instrumentGUIComponent.oscComponent.pitchSlider);
	oscWaveFormSliderAttachment = new SliderAttachment(valueTreeState, "oscWaveForm", instrumentGUIComponent.oscComponent.waveFormSlider);
	oscAttackSliderAttachment = new SliderAttachment(valueTreeState, "oscAttack", instrumentGUIComponent.oscComponent.ahfSliders[0]);
	oscHoldSliderAttachment = new SliderAttachment(valueTreeState, "oscHold", instrumentGUIComponent.oscComponent.ahfSliders[1]);
	oscFadeSliderAttachment = new SliderAttachment(valueTreeState, "oscFade", instrumentGUIComponent.oscComponent.ahfSliders[2]);
	// Delay Slider Attachments
	delay1VolumeSliderAttachment = new SliderAttachment(valueTreeState, "delay1Volume", instrumentGUIComponent.delayComponent.delayLevels[0]);
	delay2VolumeSliderAttachment = new SliderAttachment(valueTreeState, "delay2Volume", instrumentGUIComponent.delayComponent.delayLevels[1]);
	delay3VolumeSliderAttachment = new SliderAttachment(valueTreeState, "delay3Volume", instrumentGUIComponent.delayComponent.delayLevels[2]);
	delay4VolumeSliderAttachment = new SliderAttachment(valueTreeState, "delay4Volume", instrumentGUIComponent.delayComponent.delayLevels[3]);
	delay1DelaySliderAttachment = new SliderAttachment(valueTreeState, "delay1Delay", instrumentGUIComponent.delayComponent.delayTimes[0]);
	delay2DelaySliderAttachment = new SliderAttachment(valueTreeState, "delay2Delay", instrumentGUIComponent.delayComponent.delayTimes[1]);
	delay3DelaySliderAttachment = new SliderAttachment(valueTreeState, "delay3Delay", instrumentGUIComponent.delayComponent.delayTimes[2]);
	delay4DelaySliderAttachment = new SliderAttachment(valueTreeState, "delay4Delay", instrumentGUIComponent.delayComponent.delayTimes[3]);

}

CustomPercussionV2AudioProcessorEditor::~CustomPercussionV2AudioProcessorEditor()
{
}

//==============================================================================
void CustomPercussionV2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void CustomPercussionV2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
