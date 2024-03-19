# About VinceSynth

VinceSynth is a synthesizer audio plug-in using the JUCE Framework.
This synthesizer is a FM-Synthesizer or frequency modulation synthesizer.
In FM synthesis a "carrier" wave gets modulated or sculpted by another wave
to create a new sound. [More on FM Synthesis](https://en.wikipedia.org/wiki/Frequency_modulation_synthesis)

I created this synthesizer to learn about standard frameworks in music
production software, as well as C++, GUIs, microservices, and project
management with a teammate. _technologies used:_

- C++/JUCE _popular framework/C++ library used to create audio plugins_
- Python _microservice client and server language_
- XML _presets are stored in XML_
- VST3/AU \*JUCE creates the VST/AU allowing the program to work in any DAW

## Installation

1. Install [JUCE](https://github.com/juce-framework/JUCE)

2. Download and compile from source.

3. Rescan VSTs and AUs in your DAW
   This should be automatic for most DAWs plugin folder for MacOS
   ~/user/Library/Plug-ins/

Example Directory Structure:

```
 root
  ├── PluginEditor.cpp
  ├── PluginEditor.h
  ├── PluginProcessor.cpp
  ├── PluginProcessor.h
  ├── assets
  ├── data
  │   ├── AdsrData.cpp
  │   ├── AdsrData.h
  │   ├── FilterData.cpp
  │   ├── FilterData.h
  │   ├── OscData.cpp
  │   └── OscData.h
  ├── dsp
  │   ├── SynthSound.h
  │   ├── SynthVoice.cpp
  │   └── SynthVoice.h
  ├── presets
  │   ├── PresetManager.cpp
  │   ├── PresetManager.h
  │   └── PresetPanel.h
  └── ui
      ├── AdsrPanel.cpp
      ├── AdsrPanel.h
      ├── FilterPanel.cpp
      ├── FilterPanel.h
      ├── OscPanel.cpp
      └── OscPanel.h
```

## Use

VinceSynth has 5 sections: The user/preset panel, Oscillator, Amplitude envelope,
Modulation envelope, and a Filter section.
Each zone has a "?" button for quick information about each parameter.

Recommended Flow: Preset -> Oscillator -> Amp Envelope -> Mod Envelope -> Filter
-> Preset/User panel to save your settings.

### The User Panel

### The Oscillator

### The Amplitude Envelope

### The Modulation Envelope
