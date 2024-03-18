/*
  ==============================================================================

    PresetManager.h
    Created: 21 Feb 2024 7:03:17pm
    Author:  Vincewa Tran
    Description: The preset manager handles the graphics and logic for managing
    editable user info such as the presets going back and forth between presets
    and resetting to default values via a remote microservice 

  ==============================================================================
*/

#pragma once
#include <juce_audio_processors/juce_audio_processors.h> //apvts
#include <juce_gui_basics/juce_gui_basics.h> //listener and buttons

class PresetManager : juce::ValueTree::Listener
{
public:
    static const juce::File defaultDirectory;
    static const juce::String extension;
    static const juce::String presetNameProperty;

    PresetManager(juce::AudioProcessorValueTreeState&);

    void savePreset(const juce::String& presetName);
    void deletePreset(const juce::String& presetName);
    void loadPreset(const juce::String& presetName);
    void restoreDefaults();
    int loadNextPreset();
    int loadPreviousPreset();
    juce::StringArray getAllPresets() const;
    juce::String getCurrentPreset() const;
private:
    void valueTreeRedirected(juce::ValueTree& treeWhichHasBeenChanged) override;

    juce::AudioProcessorValueTreeState& valueTreeState;
    juce::Value currentPreset;
};

