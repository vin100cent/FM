/*
  ==============================================================================

    AdsrPanel.cpp
    Created: 12 Feb 2024 7:09:10pm
    Author:  Vincewa Tran
    Description: GUI output methods for the ADSR envelopes
    
  ==============================================================================
*/

#include "AdsrPanel.h"

//==============================================================================
AdsrPanel::AdsrPanel (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    componentName = name;
    
    setSliderWithLabel (attackSlider, attackLabel, apvts, attackId, attackAttachment);
    attackLabel.setTooltip("Attack");
    
    setSliderWithLabel (decaySlider, decayLabel, apvts, decayId, decayAttachment);
    decayLabel.setTooltip("Decay");
    
    setSliderWithLabel (sustainSlider, sustainLabel, apvts, sustainId, sustainAttachment);
    sustainLabel.setTooltip("Sustain");
    
    setSliderWithLabel (releaseSlider, releaseLabel, apvts, releaseId, releaseAttachment);
    releaseSlider.setTooltip("Release");
    
    addAndMakeVisible (helpButton);
    helpButton.onClick = [this] { showHelpPopup(); };
    helpButton.setTooltip("ADSR help");
}

AdsrPanel::~AdsrPanel()
{
}

void AdsrPanel::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText (componentName, labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void AdsrPanel::resized()
{
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds (attackSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    decaySlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds (decaySlider.getX(), labelStart, sliderWidth, labelHeight);
    
    sustainSlider.setBounds (decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds (sustainSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    releaseSlider.setBounds (sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds (releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    //const int helpButtonSize = 20;
    //const int helpButtonMargin = 10;
    //const int helpButtonY = bounds.getY() + 15;
    
    // Position the help button
    //helpButton.setBounds(getWidth() - helpButtonSize - helpButtonMargin, helpButtonY, helpButtonSize, helpButtonSize);

    const int helpButtonSize = 20;
    const int helpButtonMarginX = -4;
    const int helpButtonMarginY = -5;
    helpButton.setBounds(bounds.getRight() - helpButtonSize - helpButtonMarginX, bounds.getY() + helpButtonMarginY,
                         helpButtonSize, helpButtonSize);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrPanel::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

void AdsrPanel::showHelpPopup()
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "ADSR Help", "Attack: Time taken to reach peak level\nDecay: Time taken to reach sustain level\nSustain: Level at which the envelope remains\nRelease: Time taken to reach zero level", "OK");
}
