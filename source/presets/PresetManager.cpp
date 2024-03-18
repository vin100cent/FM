/*
  ==============================================================================

    PresetManager.cpp
    Created: 21 Feb 2024 7:03:17pm
    Author:  Vincewa Tran
    Description: Methods and logic for our preset manager.
    -savePreset([String] presetName)
    -deletePreset([String] presetName)
    -loadPreset([String] presetName)
    -loadNextPreset()
    -loadPreviousPreset()
    -getAllPresets()
    -getCurrentPreset()
    -valueTreeRedirected(juce::ValueTree& treeWhichHasBeenChanged)
        resets the value tree values which are all our synth parameters
 
  ==============================================================================
*/

#include "PresetManager.h"
#include <juce_core/juce_core.h>

// Convert preprocessor definitions to juce::String
const juce::String companyName = JUCE_STRINGIFY(COMPANY_NAME);
const juce::String projectName = JUCE_STRINGIFY(PROJECT_NAME);
const juce::File PresetManager::defaultDirectory{ juce::File::getSpecialLocation(
    juce::File::SpecialLocationType::commonDocumentsDirectory)
        .getChildFile(companyName)
        .getChildFile(projectName)
};
const juce::String PresetManager::extension{ "xml" };
const juce::String PresetManager::presetNameProperty{ "presetName" };


PresetManager::PresetManager(juce::AudioProcessorValueTreeState& apvts) :
    valueTreeState(apvts)
{
    // Create a default Preset Directory, if it doesn't exist
    if (!defaultDirectory.exists())
    {
        const auto result = defaultDirectory.createDirectory();
        if (result.failed())
        {
            DBG("Could not create preset directory: " + result.getErrorMessage());
            jassertfalse;
        }
    }

    valueTreeState.state.addListener(this);
    currentPreset.referTo(valueTreeState.state.getPropertyAsValue(presetNameProperty, nullptr));
}

void PresetManager::savePreset(const juce::String& presetName)
{
    if (presetName.isEmpty())
        return;

    currentPreset.setValue(presetName);
    const auto xml = valueTreeState.copyState().createXml();
    const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
    if (!xml->writeTo(presetFile))
    {
        DBG("Could not create preset file: " + presetFile.getFullPathName());
        jassertfalse;
    }
}

void PresetManager::deletePreset(const juce::String& presetName)
{
    if (presetName.isEmpty())
        return;

    const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
    if (!presetFile.existsAsFile())
    {
        DBG("Preset file " + presetFile.getFullPathName() + " does not exist");
        jassertfalse;
        return;
    }
    
    if (!presetFile.deleteFile())
    {
        DBG("Preset file " + presetFile.getFullPathName() + " could not be deleted");
        jassertfalse;
        return;
    }
    currentPreset.setValue("");
}

void PresetManager::loadPreset(const juce::String& presetName)
{
    if (presetName.isEmpty())
        return;

    const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
    if (!presetFile.existsAsFile())
    {
        DBG("Preset file " + presetFile.getFullPathName() + " does not exist");
        jassertfalse;
        return;
    }
    // presetFile (XML) -> (ValueTree)
    juce::XmlDocument xmlDocument{ presetFile };
    const auto valueTreeToLoad = juce::ValueTree::fromXml(*xmlDocument.getDocumentElement());

    valueTreeState.replaceState(valueTreeToLoad);
    currentPreset.setValue(presetName);

}

void PresetManager::restoreDefaults()
{
    
    juce::String pythonCommand = "python3 \"/Users/vincewatran/Developer/CS361/CS361 Project/sprint1/VinceSynth/zmq_client.py\" \"/Users/Shared/vincentwav/VinceSynth/preset_list.txt\"";

    juce::ChildProcess pythonProcess;
    if (pythonProcess.start(pythonCommand, juce::ChildProcess::wantStdOut | juce::ChildProcess::wantStdErr))
    {
        DBG("Process started successfully.");
        auto output = pythonProcess.readAllProcessOutput();
        DBG("Script output: " + output);

        pythonProcess.waitForProcessToFinish(10000); // Wait up to 10 seconds
        DBG("Process exit code: " + juce::String(pythonProcess.getExitCode()));
    }
    else
    {
        DBG("Failed to start the process.");
    }
}


int PresetManager::loadNextPreset()
{
    const auto allPresets = getAllPresets();
    if (allPresets.isEmpty())
        return -1;
    const auto currentIndex = allPresets.indexOf(currentPreset.toString());
    const auto nextIndex = currentIndex + 1 > (allPresets.size() - 1) ? 0 : currentIndex + 1;
    loadPreset(allPresets.getReference(nextIndex));
    return nextIndex;
}

int PresetManager::loadPreviousPreset()
{
    const auto allPresets = getAllPresets();
    if (allPresets.isEmpty())
        return -1;
    const auto currentIndex = allPresets.indexOf(currentPreset.toString());
    const auto previousIndex = currentIndex - 1 < 0 ? allPresets.size() - 1 : currentIndex - 1;
    loadPreset(allPresets.getReference(previousIndex));
    return previousIndex;
}

juce::StringArray PresetManager::getAllPresets() const
{
    juce::StringArray presets;
    const auto fileArray = defaultDirectory.findChildFiles(
        juce::File::TypesOfFileToFind::findFiles, false, "*." + extension);
    for (const auto& file : fileArray)
    {
        presets.add(file.getFileNameWithoutExtension());
    }
    return presets;
}

juce::String PresetManager::getCurrentPreset() const
{
    return currentPreset.toString();
}

void PresetManager::valueTreeRedirected(juce::ValueTree& treeWhichHasBeenChanged)
{
    currentPreset.referTo(treeWhichHasBeenChanged.getPropertyAsValue(presetNameProperty, nullptr));
}

