/*
  ==============================================================================

    SynthVoice.cpp
    Created: 12 Feb 2024 7:04:01pm
    Author:  Vincewa Tran

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency (midiNoteNumber);
    adsr.noteOn();
    filterAdsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    filterAdsr.noteOff();
    
    if (! allowTailOff || ! adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepareToPlay (spec);
    filterAdsr.setSampleRate (sampleRate);
    filter.prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
    adsr.setSampleRate (sampleRate);
    gain.prepare (spec);
    
    gain.setGainLinear (0.3f);
    
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    
    if (! isVoiceActive())
        return;
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    filterAdsr.applyEnvelopeToBuffer (outputBuffer, 0, numSamples);
    synthBuffer.clear();
        
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock (audioBlock);
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process (synthBuffer);
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (! adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::updateFilter (const int filterType, const float frequency, const float resonance)
{
    auto modulator = filterAdsr.getNextSample();
    filter.updateParameters (modulator, filterType, frequency, resonance);
}
