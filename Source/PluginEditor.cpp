#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloROMplerAudioProcessorEditor::HelloROMplerAudioProcessorEditor(HelloROMplerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), adsrComponent(p.parameters) {
    // ComboBox
    addAndMakeVisible(sampleSelectionBox);
    sampleSelectionBox.onChange = [this] { this->sampleSelectionChanged(); };
    populateSampleSelectionBox();

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
//==============================================================================
void HelloROMplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello Rompler!", getLocalBounds(), juce::Justification::centred, 1);
}

// PluginEditor.cpp

void HelloROMplerAudioProcessorEditor::resized() {
    auto area = getLocalBounds(); // Ottiene l'area totale della finestra

    auto headerArea = area.removeFromTop(100); // Area dell'header per ComboBox e ADSRComponent

    // Definizione delle proporzioni dell'area dell'intestazione per ComboBox e ADSRComponent
    int comboBoxWidthProportion = 1; // Parte dell'area dell'intestazione per la ComboBox
    int adsrWidthProportion = 3; // Parte dell'area dell'intestazione per l'ADSRComponent
    int totalProportion = comboBoxWidthProportion + adsrWidthProportion;

    // Posiziona la ComboBox
    auto comboBoxArea = headerArea.removeFromLeft(headerArea.getWidth() * comboBoxWidthProportion / totalProportion);
    sampleSelectionBox.setBounds(comboBoxArea.reduced(10)); // Riduci per avere un po' di margine

    // Posiziona l'ADSRComponent nell'area rimanente
    adsrComponent.setBounds(headerArea.reduced(5));

    // ... logica per posizionare altri controlli se presenti ...
}


