#include "PluginEditor.h"

VinceSynthAudioProcessorEditor::VinceSynthAudioProcessorEditor (VinceSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
      , presetPanel (p.getPresetManager())
      , audioProcessor (p)
      , osc (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
      , adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
      , filterAdsr ("Mod Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
      , filter (audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
      , tooltipWindow(this)
      , processorRef (p)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible (inspectButton);

    // this chunk of code instantiates and opens the melatonin inspector
    inspectButton.onClick = [&] {
        if (!inspector)
        {
            inspector = std::make_unique<melatonin::Inspector> (*this);
            inspector->onClose = [this]() { inspector.reset(); };
        }

        inspector->setVisible (true);
    };

    setSize (620, 540);
    addAndMakeVisible (presetPanel);
    addAndMakeVisible (osc);
    addAndMakeVisible (adsr);
    addAndMakeVisible (filterAdsr);
    addAndMakeVisible (filter);

    documentation.setButtonText("Help");
    documentation.onClick = [this]{
        juce::URL("https://github.com/vin100cent/VinceSynth").launchInDefaultBrowser(); };
    addAndMakeVisible(documentation);

}

VinceSynthAudioProcessorEditor::~VinceSynthAudioProcessorEditor()
{
}

void VinceSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::saddlebrown);

}

void VinceSynthAudioProcessorEditor::resized()
{

    auto bounds = getLocalBounds();

    // Preset Panel Height
    const auto topSectionHeight = proportionOfHeight(0.2f);
    presetPanel.setBounds(bounds.removeFromTop(topSectionHeight));

    // Calculate space for undo, redo, and documentation buttons
    const int paddingY = topSectionHeight;
    const int paddingX = 10;
    const int paddingY2 = paddingY + 200;

    // Position for documentation button
    documentation.setBounds(496, 56, 116, 30);

    osc.setBounds(paddingX, paddingY, 300, 200);
    adsr.setBounds(osc.getRight(), paddingY, 300, 200);
    filterAdsr.setBounds(paddingX, paddingY2, 300, 200);
    filter.setBounds(filterAdsr.getRight(), paddingY2, 300, 200);

    // Positioning inspectButton below everything else
    int lowestPoint = paddingY2 + 200;
    int inspectButtonHeight = 50;
    int inspectButtonWidth = 100;

    // Calculate the starting Y position for inspectButton by adding some margin (let's say 10 pixels) below the lowest component
    int inspectButtonYPos = lowestPoint + 10; // Adjust the margin as needed

    // Now, position inspectButton centered horizontally and at the calculated Y position vertically
    inspectButton.setBounds(getLocalBounds().withTrimmedTop(inspectButtonYPos).withSizeKeepingCentre(inspectButtonWidth, inspectButtonHeight));

}
