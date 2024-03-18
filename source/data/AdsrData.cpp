/*
  ==============================================================================

    AdsrData.cpp
    Created: 12 Feb 2024 7:10:19pm
    Author:  Vincewa Tran
    Description: update method for the ADSR values 

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update (const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters (adsrParams);
}
