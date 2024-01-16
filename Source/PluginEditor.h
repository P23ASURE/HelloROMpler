
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    juce::ComboBox sampleSelectionBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> comboBoxAttachment;

    std::vector<float> audioPoints;

    HelloROMplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloROMplerAudioProcessorEditor)
};
