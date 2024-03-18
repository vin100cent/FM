/*
  ==============================================================================

    OscPanel.cpp
    Created: 12 Feb 2024 7:13:41pm
    Author:  Vincewa Tran
    Description: GUI output methods for the oscillator panel

  ==============================================================================
*/

#include "OscPanel.h"

//==============================================================================
OscPanel::OscPanel (juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray choices { "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList (choices, 1);
    addAndMakeVisible (oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
    waveSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont (15.0f);
    waveSelectorLabel.setJustificationType (juce::Justification::left);
    waveSelectorLabel.setTooltip("? for details");
    addAndMakeVisible (waveSelectorLabel);
    
    setSliderWithLabel (fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);
    fmFreqLabel.setTooltip("Frequency Modulation Hz");
    
    setSliderWithLabel (fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);
    fmDepthLabel.setTooltip("Modulation Depth Hz");
    
    // add help button
    addAndMakeVisible (helpButton);
    helpButton.onClick = [this] { showHelpPopup(); };
    helpButton.setTooltip("Osc help");
}

OscPanel::~OscPanel()
{
}

void OscPanel::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Oscillator", labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void OscPanel::resized()
{
    const auto bounds = getLocalBounds().reduced (10);

    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    oscWaveSelector.setBounds (10, startY + 5, 90, 30);
    waveSelectorLabel.setBounds (10, startY - labelYOffset, 90, labelHeight);
    
    fmFreqSlider.setBounds (oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds (fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);

    fmDepthSlider.setBounds (fmFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds (fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
    
    
    const int helpButtonSize = 20;
    const int helpButtonMarginX = -4;
    const int helpButtonMarginY = -5;
    helpButton.setBounds(bounds.getRight() - helpButtonSize - helpButtonMarginX, bounds.getY() + helpButtonMarginY,
                         helpButtonSize, helpButtonSize);
    
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscPanel::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
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

void OscPanel::showHelpPopup()
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "Oscillator Help", "The oscillator produces the sound\nWave Type: the shape of the wave produced\nFM Freq: Modulates the frequency of the wave form\nMod Depth: Modulates the harmonic character of the source sound.", "OK");
}
