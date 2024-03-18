/*
  ==============================================================================

    SynthSound.h
    Created: 12 Feb 2024 7:04:36pm
    Author:  Vincewa Tran

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
    
};
