/*
  ==============================================================================

    FilterPanel.cpp
    Created: 12 Feb 2024 7:18:53pm
    Author:  Vincewa Tran
    Description: GUI output methods for the synth filter


  ==============================================================================
*/

#include "FilterPanel.h"

//==============================================================================
FilterPanel::FilterPanel (juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId)
{
    juce::StringArray choices { "Low", "Band", "High" };
    filterTypeSelector.addItemList (choices, 1);
    addAndMakeVisible (filterTypeSelector);
    filterTypeSelector.setTooltip("Cutoff from lo, mid, or hi");
    
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);
    
    filterSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont (15.0f);
    filterSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (filterSelectorLabel);
    
    setSliderWithLabel (filterFreqSlider, filterFreqLabel, apvts, filterFreqId, filterFreqAttachment);
    filterFreqLabel.setTooltip("Filter Frequency");
    
    setSliderWithLabel (filterResSlider, filterResLabel, apvts, filterResId, filterResAttachment);
    filterResLabel.setTooltip("Filter Resonance");
    
    // add help button
    addAndMakeVisible (helpButton);
    helpButton.onClick = [this] { showHelpPopup(); };
    helpButton.setTooltip("Filter help");
}

FilterPanel::~FilterPanel()
{
}

void FilterPanel::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Filter", labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void FilterPanel::resized()
{
    const auto bounds = getLocalBounds().reduced (10);
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    filterTypeSelector.setBounds (10, startY + 5, 90, 30);
    filterSelectorLabel.setBounds (10, startY - labelYOffset, 90, labelHeight);
    
    filterFreqSlider.setBounds (filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    filterFreqLabel.setBounds (filterFreqSlider.getX(), filterFreqSlider.getY() - labelYOffset, filterFreqSlider.getWidth(), labelHeight);

    filterResSlider.setBounds (filterFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds (filterResSlider.getX(), filterResSlider.getY() - labelYOffset, filterResSlider.getWidth(), labelHeight);
    
    const int helpButtonSize = 20;
    const int helpButtonMarginX = -4;
    const int helpButtonMarginY = -5;
    helpButton.setBounds(bounds.getRight() - helpButtonSize - helpButtonMarginX, bounds.getY() + helpButtonMarginY,
                         helpButtonSize, helpButtonSize);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterPanel::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

void FilterPanel::showHelpPopup()
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "Filter Help", "Type: Sculpt the sound by taking off the low middle or high frequencies.\nFrequency: Change the center from where the cutoff is happening.\nResonance: Emphasizes a specific frequency.", "OK");
}
