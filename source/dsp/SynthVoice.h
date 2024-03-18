/*
  ==============================================================================

    SynthVoice.h
    Created: 12 Feb 2024 7:04:01pm
    Author:  Vincewa Tran

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include "SynthSound.h"
#include "../source/data/OscData.h"
#include "../source/data/AdsrData.h"
#include "../source/data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateFilter (const int filterType, const float frequency, const float resonance);
    
    OscData& getOscillator() { return osc; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return filterAdsr; }
    FilterData& getFilter() { return filter; }
    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    OscData osc;
    AdsrData adsr;
    AdsrData filterAdsr;
    FilterData filter;
    juce::dsp::Gain<float> gain;
    
    bool isPrepared { false };
};
