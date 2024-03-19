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

    setSize (620, 540);
    addAndMakeVisible (presetPanel);
    addAndMakeVisible (osc);
    addAndMakeVisible (adsr);
    addAndMakeVisible (filterAdsr);
    addAndMakeVisible (filter);

    addAndMakeVisible(startButton);
    addAndMakeVisible(hintButton);
    addAndMakeVisible (inspectButton);
    addAndMakeVisible(documentation);

    documentation.onClick = [&] { juce::URL("https://github.com/vin100cent/VinceSynth").launchInDefaultBrowser(); };
    startButton.onClick = [&] { showStartPopup(); };
    hintButton.onClick = [&] { showHintPopup(); };

    // this chunk of code instantiates and opens the melatonin inspector
    inspectButton.onClick = [&] {
        if (!inspector)
        {
            inspector = std::make_unique<melatonin::Inspector> (*this);
            inspector->onClose = [this]() { inspector.reset(); };
        }

        inspector->setVisible (true);
    };

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

    // help section
    startButton.setBounds(paddingX, 56, 82, 30);
    hintButton.setBounds(startButton.getRight()+paddingX, 56, 82, 30);
    documentation.setBounds(496, 56, 116, 30);

    // Synth sections
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
    inspectButton.setBounds(getLocalBounds().withTrimmedTop(inspectButtonYPos).withSizeKeepingCentre(inspectButtonWidth, inspectButtonHeight));
}

void VinceSynthAudioProcessorEditor::showStartPopup()
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "Vinny Synth 1.0", "A simple soft synth to learn the basics of FM Synthesis\nRecommended flow: Osc->Mod->Env->Filter\nReadme or ? for detailed information\nHint for synth functions", "Done");
}

void VinceSynthAudioProcessorEditor::showHintPopup()
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "Hints", "Use built in DAW buttons or CtrlZ/Ctrl+Shift+Z for undo/redo\nRestore Presets to recover defaults\nPresets will be in the folder ~/shared/COMPANY_NAME/PROJECT_NAME\nAttach midi or virtual midi input to trigger synth.", "Done");
}

