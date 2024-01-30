
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSRComponent.h"
//==============================================================================
/**
*/
class HelloROMplerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HelloROMplerAudioProcessorEditor (HelloROMplerAudioProcessor&);
    ~HelloROMplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void populateSampleSelectionBox();
    void sampleSelectionChanged();
private:
    juce::Slider gainSlider; 
    juce::Label gainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    ADSRComponent adsrComponent;

    // ADSR Slider & Label
    juce::Slider attackSlider;
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Label sustainLabel;
    juce::Slider releaseSlider;
    juce::Label releaseLabel;
    // ADSR APVTS
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    // Sample Selection - Combo Box
    juce::ComboBox sampleSelectionBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> comboBoxAttachment;

    std::vector<float> audioPoints;

    HelloROMplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloROMplerAudioProcessorEditor)
};
