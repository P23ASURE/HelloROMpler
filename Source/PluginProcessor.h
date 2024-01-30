
#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================
/**
*/
class HelloROMplerAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    HelloROMplerAudioProcessor();
    ~HelloROMplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    std::atomic<bool>& isNotPlayed() { return isNotePlayed; }
    std::atomic<int>& getSampleCount() { return sampleCount; }
    
    void selectSample(int index);
    const juce::Array<juce::File>& getSampleFiles() const { return sampleFiles; }
    juce::AudioProcessorValueTreeState parameters;
    void updateADSRIfNecessary();
    int getCurrentSampleIndex() const;
private:

    std::atomic<float>* gainParameter;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    std::vector<float> adsrValues;
    
    void loadSamplesFromROM();
    juce::Array<juce::File> sampleFiles;
    int currentSampleIndex = 0;

    juce::Synthesiser mySampler;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReader> formatReader;

    std::atomic<bool> isNotePlayed{ false };
    std::atomic<int> sampleCount{ 0 };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloROMplerAudioProcessor)
};
