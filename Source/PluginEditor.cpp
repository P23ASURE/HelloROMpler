#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloROMplerAudioProcessorEditor::HelloROMplerAudioProcessorEditor (HelloROMplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(sampleSelectionBox);
    sampleSelectionBox.onChange = [this] { this->sampleSelectionChanged(); };
    populateSampleSelectionBox();
    
    setSize (700, 500);
}

HelloROMplerAudioProcessorEditor::~HelloROMplerAudioProcessorEditor()
{
}

//==============================================================================

void HelloROMplerAudioProcessorEditor::populateSampleSelectionBox() {
    sampleSelectionBox.clear();
    for (auto& file : audioProcessor.getSampleFiles()) {
        sampleSelectionBox.addItem(file.getFileNameWithoutExtension(), sampleSelectionBox.getNumItems() + 1);
    }
    
}

void HelloROMplerAudioProcessorEditor::sampleSelectionChanged() {
    int selectedSampleIndex = sampleSelectionBox.getSelectedItemIndex();
    audioProcessor.selectSample(selectedSampleIndex);
}
//==============================================================================
void HelloROMplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello Rompler!", getLocalBounds(), juce::Justification::centred, 1);
}

void HelloROMplerAudioProcessorEditor::resized()
{
    sampleSelectionBox.setBounds(10, 10, 150, 30);
}
