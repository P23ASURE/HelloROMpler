/*
  ==============================================================================

    ADSRComponent.h
    Created: 25 Jan 2024 9:56:49am
    Author:  Marco

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRComponent : public juce::Component {
public:
    ADSRComponent(juce::AudioProcessorValueTreeState& vts);
    ~ADSRComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    juce::AudioProcessorValueTreeState& valueTreeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRComponent)
};

