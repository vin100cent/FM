/*
  ==============================================================================

    FilterPanel.h
    Created: 12 Feb 2024 7:18:53pm
    Author:  Vincewa Tran

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
//==============================================================================
/*
*/
class FilterPanel  : public juce::Component
{
public:
    FilterPanel (juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FilterPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // drop down menu for filter type 
    juce::ComboBox filterTypeSelector { "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;
    
    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> filterFreqAttachment;
    std::unique_ptr<Attachment> filterResAttachment;
    
    juce::Label filterSelectorLabel { "Filter Type", "Type" };
    juce::Label filterFreqLabel { "Filter Freq", "Freq" };
    juce::Label filterResLabel { "Filter Res", "Res" };
    
    juce::TextButton helpButton {"?"};
    void showHelpPopup();
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterPanel)
};
