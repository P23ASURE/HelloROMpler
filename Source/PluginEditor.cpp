#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloROMplerAudioProcessorEditor::HelloROMplerAudioProcessorEditor(HelloROMplerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), adsrComponent(p.parameters) {
    // Inizializza il pulsante "Next"
    nextButton.setButtonText("Next");
    nextButton.onClick = [this] { audioProcessor.nextSample(); updateComboBoxSelection(); };
    addAndMakeVisible(nextButton);

    // Inizializza il pulsante "Previous"
    previousButton.setButtonText("Previous");
    previousButton.onClick = [this] { audioProcessor.previousSample(); updateComboBoxSelection(); };
    addAndMakeVisible(previousButton);

    // Configure the gain slider
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainSlider.setRange(0.0, 1.0, 1.0);
    addAndMakeVisible(gainSlider);

    // Configure the gain label
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);
    addAndMakeVisible(gainLabel);

    // Attach the slider to the gain parameter
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "gain", gainSlider);

    // ComboBox
    addAndMakeVisible(sampleSelectionBox);
    sampleSelectionBox.onChange = [this] { this->sampleSelectionChanged(); };
    populateSampleSelectionBox();
    int currentSampleIndex = audioProcessor.getCurrentSampleIndex();
    if (currentSampleIndex >= 0 && currentSampleIndex < sampleSelectionBox.getNumItems()) {
        sampleSelectionBox.setSelectedItemIndex(currentSampleIndex, juce::dontSendNotification);
    }

    addAndMakeVisible(adsrComponent);

    setSize(700, 500);
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

void HelloROMplerAudioProcessorEditor::updateComboBoxSelection() {
    int currentSampleIndex = audioProcessor.getCurrentSampleIndex();
    if (currentSampleIndex >= 0 && currentSampleIndex < sampleSelectionBox.getNumItems()) {
        sampleSelectionBox.setSelectedItemIndex(currentSampleIndex, juce::dontSendNotification);
    }
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


void HelloROMplerAudioProcessorEditor::resized() {
    auto area = getLocalBounds();
    auto headerArea = area.removeFromTop(100);
    int comboBoxWidthProportion = 1;
    int adsrWidthProportion = 4;
    int gainWidthProportion = 1;
    int totalProportion = comboBoxWidthProportion + adsrWidthProportion + gainWidthProportion;

    // ComboBox Area
    auto comboBoxArea = headerArea.removeFromLeft(headerArea.getWidth() * comboBoxWidthProportion / totalProportion);
    sampleSelectionBox.setBounds(comboBoxArea.reduced(10));

    // ADSR Component Area
    auto adsrArea = headerArea.removeFromLeft(headerArea.getWidth() * adsrWidthProportion / totalProportion);
    adsrComponent.setBounds(adsrArea.reduced(5));

    // Gain Area (now further to the right)
    auto gainArea = headerArea; // Use the remaining area for the gain

    // Gain Slider Area
    auto sliderHeight = gainArea.proportionOfHeight(0.8); // Allocate 80% of the gain area height for the slider
    gainSlider.setBounds(gainArea.removeFromTop(sliderHeight).reduced(10)); // Position the slider, add some padding

    // Gain Label Area (below the slider)
    // Ensure the remaining area is for the label, adjust padding if needed
    // Check if the height is too small and adjust accordingly
    if (gainArea.getHeight() < 20) { // Minimum height for the label
        gainArea = gainArea.withHeight(20);
    }
    gainLabel.setBounds(gainArea.reduced(10, 0)); // Reduce left and right padding, but no top and bottom padding
    gainLabel.setJustificationType(juce::Justification::centred); // Center the label text

    // Posiziona i pulsanti "Next" e "Previous"
    const int buttonHeight = 30;
    const int buttonWidth = 100;
    nextButton.setBounds(getWidth() - buttonWidth - 10, getHeight() - buttonHeight - 10, buttonWidth, buttonHeight);
    previousButton.setBounds(10, getHeight() - buttonHeight - 10, buttonWidth, buttonHeight);
}
