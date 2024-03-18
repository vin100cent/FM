/*
  ==============================================================================

    OscData.h
    Created: 12 Feb 2024 7:12:54pm
    Author:  Vincewa Tran

  ==============================================================================
*/

#pragma once
#include <juce_dsp/juce_dsp.h>


//==============================================================================
/*
*/
class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setWaveType (const int choice);
    void setWaveFrequency (const int midiNoteNumber);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    void updateFm (const float freq, const float depth);
    
private:
    void processFmOsc (juce::dsp::AudioBlock<float>& block);
    
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); } };
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int lastMidiNote { 0 };
};
