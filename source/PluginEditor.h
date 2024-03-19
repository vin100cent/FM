#pragma once

#include "PluginProcessor.h"
#include "BinaryData.h"
#include "melatonin_inspector/melatonin_inspector.h"
#include "../source/ui/AdsrPanel.h"
#include "../source/ui/OscPanel.h"
#include "../source/ui/FilterPanel.h"
#include "../source/presets/PresetPanel.h"


//==============================================================================
class VinceSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    VinceSynthAudioProcessorEditor (VinceSynthAudioProcessor&);
    ~VinceSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void showHintPopup();
    void showStartPopup();

private:

    // Panels that exist as their own files/components
    PresetPanel presetPanel;
    VinceSynthAudioProcessor& audioProcessor;
    OscPanel osc;
    AdsrPanel adsr;
    AdsrPanel filterAdsr;
    FilterPanel filter;

    //help section
    juce::TooltipWindow tooltipWindow;
    juce::TextButton startButton {"Start"};
    juce::TextButton hintButton {"Hint"};
    juce::TextButton documentation {"Readme"};

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VinceSynthAudioProcessor& processorRef;
    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton { "Inspect the UI" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VinceSynthAudioProcessorEditor)
};
