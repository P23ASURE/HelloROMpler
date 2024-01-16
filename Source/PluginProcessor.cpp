/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloROMplerAudioProcessor::HelloROMplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    formatManager.registerBasicFormats();

    for (int i = 0; i < 3; i++)
    {
        mySampler.addVoice(std::make_unique<juce::SamplerVoice>().release());
    }


    loadSamplesFromROM();
}

HelloROMplerAudioProcessor::~HelloROMplerAudioProcessor()
{
}

//==============================================================================
void HelloROMplerAudioProcessor::selectSample(int index) {
    if (index >= 0 && index < sampleFiles.size()) {
        auto file = sampleFiles[index];
        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
        if (reader) {
            juce::BigInteger range;
            range.setRange(0, 128, true);
            mySampler.clearSounds();
            mySampler.addSound(new juce::SamplerSound(file.getFileNameWithoutExtension(), *reader, range, 60, 0.1, 0.1, 10));
        }
        else {
            DBG("Unable to create a reader for the file: " << file.getFullPathName());
        }
    }
}

void HelloROMplerAudioProcessor::loadSamplesFromROM() {
    juce::File appDirectory = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory();
    juce::File romDirectory = appDirectory.getChildFile("Resources/ROM");
    sampleFiles.clear();  // Pulire l'array prima di popolarlo
    romDirectory.findChildFiles(sampleFiles, juce::File::findFiles, false, "*.wav");

    if (!sampleFiles.isEmpty()) {
        selectSample(0);  // Seleziona il primo campione per default
    }
    else {
        DBG("No .wav files found in " << romDirectory.getFullPathName());
    }
}
//==============================================================================
const juce::String HelloROMplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HelloROMplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HelloROMplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HelloROMplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HelloROMplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HelloROMplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HelloROMplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HelloROMplerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HelloROMplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void HelloROMplerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HelloROMplerAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mySampler.setCurrentPlaybackSampleRate(sampleRate);

}

void HelloROMplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloROMplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HelloROMplerAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    juce::MidiMessage m;
    juce::MidiBuffer::Iterator it{ midiMessages };
    int sample;

    while (it.getNextEvent(m, sample))
    {
        if (m.isNoteOn())
            isNotePlayed = true;
        else if (m.isNoteOff())
            isNotePlayed = false;
    }

    sampleCount = isNotePlayed ? sampleCount += buffer.getNumSamples() : 0;

    mySampler.renderNextBlock(buffer,
        midiMessages,
        0,
        buffer.getNumSamples());

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        // 
    }
}

//==============================================================================
bool HelloROMplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HelloROMplerAudioProcessor::createEditor()
{
    return new HelloROMplerAudioProcessorEditor (*this);
}

//==============================================================================
void HelloROMplerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HelloROMplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloROMplerAudioProcessor();
}
