# About VinnySynth

VinnySynth is a synthesizer audio plug-in using the JUCE Framework.
This synthesizer is a FM-Synthesizer or frequency modulation synthesizer.
In FM synthesis a "carrier" wave gets modulated or sculpted by another wave
to create a new sound. [More on FM Synthesis](https://en.wikipedia.org/wiki/Frequency_modulation_synthesis)

This is a great synthesizer for learning some FM synthesis basics without all the complexity of a full FM synth.
It builds into a VST3 and AU plugin so you can use it in any DAW!

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

The user panel is where you can save and load presets. The smaller buttons below
the preset buttons are buttons for restoring default preset values via an editable .txt file.

The location of the presets are defined by the CMAKELists.txt file in the JUCE project.

```cmake
target_compile_definitions(SharedCode
    INTERFACE
        PROJECT_NAME=${PROJECT_NAME}
        COMPANY_NAME=${COMPANY_NAME}
```

which saves the presets in the following directory:

```zsh
~src/Shared/COMPANY_NAME/PROJECT_NAME
```

The zmq microservice uses the preset_list.txt to find the names of the defualt presets
and rewrites the file in the local folder with the same name to restore default values.
User created presets will not be affected by this. This means the user can feel free to
experiment with the default presets to create their own and recover the original in the case
of accidendtally saving a user preset with the same name as a defualt preset.

### The Oscillator

This is the sound source of the synthesizer. It's two waves one that's a modulator wave
that create new sounds by modulating the frequency of the other wave "carrier wave".
The carrier wave is the sound that is heard, and the modulator wave is the wave
that changes the carrier wave.

The Oscillator section has 3 parameters:
the frequency, the modulation index, and the waveform.
The waveform is the shape of the carrier wave.
The frequency is the pitch of the sound
The modulation index is the amount of modulation applied to the carrier wave.

This synth has 3 waveforms:
Sin-characterized by its smooth, round sound (ex: a flute)
Saw-characterized by its bright, buzzy sound (ex: a chainsaw)
Square-characterized by its hollow, nasal sound (ex: guitar distortion)

### The Amplitude Envelope

The amplitude envelope is the volume of the sound over time. It has 4 parameters:
**A**ttack-the time it takes for the sound to reach its maximum volume
**D**ecay-the time it takes for the sound to reach its sustain level
**S**ustain-the level of the sound after the decay
**R**elease-the time it takes for the sound to fade out after the key is released

Example of amplitude envelope for a pluck sound:
attack: 0.1s
decay: 0.2s
sustain: 0.5
release: 0.3s

### The Modulation Envelope

The modulation envelope is the amount of modulation applied to the carrier wave over time.
Like the amplitude envelope, it has 4 parameters:
**A**ttack-the time it takes for the sound to reach its maximum modulation index
**D**ecay-the time it takes for the sound to reach its sustain level
**S**ustain-the level of the sound after the decay
**R**elease-the time it takes for the sound to fade out after the key is released

Example of modulation envelope for a pad sound:
attack: 1s
decay: 3s
sustain: 0.5
release: 2s

### The Filter

In a synthesizer, the filter is used to sculpt the sound by removing certain frequencies.
It works by cutting off frequencies by cutting or boosting the frequencies above or below a certain frequency.
The filter has 3 parameters:
A drop down with low, band, and high pass filters-do you want to cut off the low, middle, or high frequencies?
Frequency-The frequency at which the filter starts to cut off frequencies
Resonance-The amount of boost at the cutoff frequency

Examples:
For a kick drum, you might want a low pass filter to cut off the high frequencies, and a high resonance to boost the low frequencies.
