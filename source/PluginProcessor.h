#pragma once

#include <stack>
#include <juce_audio_processors/juce_audio_processors.h>
#include "../source/presets/PresetManager.h"
#include "../source/dsp/SynthSound.h"
#include "../source/dsp/SynthVoice.h"
#include "../source/data/AdsrData.h"

#if (MSVC)
#include "ipps.h"
#endif

class VinceSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    VinceSynthAudioProcessor();
    ~VinceSynthAudioProcessor() override;

    //===Synth Voice Methods========================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //====GUI=======================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //====Midi Functions============================================================
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

    //====State Functions===========================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //====Undo/Redo Functions=======================================================

    void undo();
    void redo();
    void captureState();

    PresetManager& getPresetManager() { return *presetManager; }
    juce::AudioProcessorValueTreeState apvts;
private:
    std::unique_ptr<PresetManager> presetManager;
    juce::Synthesiser synth;
    std::stack<juce::ValueTree> undoStack, redoStack;
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VinceSynthAudioProcessor)
};
