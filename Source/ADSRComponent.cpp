/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 25 Jan 2024 9:56:49am
    Author:  Marco

  ==============================================================================
*/

#include "ADSRComponent.h"

ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& vts)
    : valueTreeState(vts) {

    // ** ADSR SLIDER
    // Attack Slider
    attackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(0.1f, 5000.0f, 0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    addAndMakeVisible(&attackSlider);
    attackAttachment.reset(new SliderAttachment(valueTreeState, "attack", attackSlider));

    // Decay Slider
    decaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setRange(0.1f, 2000.0f, 0.1f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    addAndMakeVisible(&decaySlider);
    decayAttachment.reset(new SliderAttachment(valueTreeState, "decay", decaySlider));

    // Sustain Slider
    sustainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sustainSlider.setRange(0.0f, 1.0f, 0.01f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    addAndMakeVisible(&sustainSlider);
    sustainAttachment.reset(new SliderAttachment(valueTreeState, "sustain", sustainSlider));

    // Release Slider
    releaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setRange(0.1f, 5000.0f, 0.1f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    addAndMakeVisible(&releaseSlider);
    releaseAttachment.reset(new SliderAttachment(valueTreeState, "release", releaseSlider));

    // ** ADSR labels
    // Attack
    attackLabel.setText("A", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&attackLabel);
    // Decay
    decayLabel.setText("D", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&decayLabel);
    // Sustain
    sustainLabel.setText("S", juce::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&sustainLabel);
    // Release
    releaseLabel.setText("R", juce::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&releaseLabel);

    // setSize(300, 200);
}

ADSRComponent::~ADSRComponent() {
}

void ADSRComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

void ADSRComponent::resized() {
    auto area = getLocalBounds(); 
    int numSliders = 4; 
    int labelHeight = 20;

    for (int i = 0; i < numSliders; ++i) {
        auto singleSliderArea = area.removeFromLeft(area.getWidth() / (numSliders - i)).reduced(5);
        auto labelArea = singleSliderArea.removeFromBottom(labelHeight); 

        switch (i) {
        case 0:
            attackSlider.setBounds(singleSliderArea);
            attackLabel.setBounds(labelArea);
            break;
        case 1:
            decaySlider.setBounds(singleSliderArea);
            decayLabel.setBounds(labelArea);
            break;
        case 2:
            sustainSlider.setBounds(singleSliderArea);
            sustainLabel.setBounds(labelArea);
            break;
        case 3:
            releaseSlider.setBounds(singleSliderArea);
            releaseLabel.setBounds(labelArea);
            break;
        }
    }
}

