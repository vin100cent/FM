/*
  ==============================================================================

    PresetPanel.h
    Created: 21 Feb 2024 7:14:09pm
    Author:  Vincewa Tran
    Description: UI for our services such as the preset manager, help/info, and
    the GUI interface between the microservice and the synthesizer
    -buttons and dropdowns 

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../source/presets/PresetManager.h"


class PresetPanel : public juce::Component, juce::Button::Listener, juce::ComboBox::Listener
{
public:
    explicit PresetPanel(PresetManager& pm) : presetManager(pm)
    {
        configureButton(saveButton, "Save");
        configureButton(deleteButton, "Delete");
        configureButton(previousPresetButton, "<");
        configureButton(nextPresetButton, ">");
        configureButton(restoreDefaultsButton, "Refresh Presets");

        presetList.setTextWhenNothingSelected("No Preset Selected");
        presetList.setMouseCursor(juce::MouseCursor::PointingHandCursor);
        addAndMakeVisible(presetList);
        presetList.addListener(this);

        loadPresetList();
    }

    ~PresetPanel()
    {
        saveButton.removeListener(this);
        deleteButton.removeListener(this);
        previousPresetButton.removeListener(this);
        nextPresetButton.removeListener(this);
        restoreDefaultsButton.removeListener(this);
        presetList.removeListener(this);
    }
    
    void paint(juce::Graphics& g) override
    {
    }

    void resized() override
    {
        const auto container = getLocalBounds().reduced(4);
            auto bounds = container;

            // Calculate button heights based on the new container height
            // The proportions here are just an example; adjust as necessary for your layout
            const auto buttonHeight = container.proportionOfHeight(0.5f); // Adjust this proportion to fit
            const int gap = 4; // Gap between buttons
            
            // Assuming all buttons have the same height now
            saveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).withHeight(buttonHeight).reduced(gap));
            previousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).withHeight(buttonHeight).reduced(gap));
            presetList.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.4f)).withHeight(buttonHeight).reduced(gap));
            nextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).withHeight(buttonHeight).reduced(gap));
            deleteButton.setBounds(bounds.withHeight(buttonHeight).reduced(gap));

            // Adjust the layout for the restoreDefaultsButton considering the increased panel height
            restoreDefaultsButton.setBounds(
                presetList.getX(), // Align left edge with saveButton
                deleteButton.getBottom() + gap, // Position below the other buttons with a gap
                presetList.getWidth(), // Width to fit within the panel minus padding
                30// Height based on the new proportion
            );
        
    }
private:
    void buttonClicked(juce::Button* button) override
    {
        if (button == &saveButton)
        {
            fileChooser = std::make_unique<juce::FileChooser>(
                "Please enter the name of the preset to save",
                PresetManager::defaultDirectory,
                "*." + PresetManager::extension
            );
            fileChooser->launchAsync(juce::FileBrowserComponent::saveMode, [&](const juce::FileChooser& chooser)
                {
                    const auto resultFile = chooser.getResult();
                    presetManager.savePreset(resultFile.getFileNameWithoutExtension());
                    loadPresetList();
                });
        }
        if (button == &previousPresetButton)
        {
            const auto index = presetManager.loadPreviousPreset();
            presetList.setSelectedItemIndex(index, juce::dontSendNotification);
        }
        if (button == &nextPresetButton)
        {
            const auto index = presetManager.loadNextPreset();
            presetList.setSelectedItemIndex(index, juce::dontSendNotification);
        }
        if (button == &deleteButton)
        {
            //heuristic 8 tinker mindfully
            auto* confirmDeleteDialog = new juce::AlertWindow("Confirm Deletion",
                                                              "Are you sure you want to delete the preset '" + presetManager.getCurrentPreset() + "'?",
                                                              juce::AlertWindow::WarningIcon);
            confirmDeleteDialog->addButton("Yes", 1); // 1: return key identifier
            confirmDeleteDialog->addButton("No", 0, juce::KeyPress(juce::KeyPress::escapeKey)); // 0: escape key identifier

            confirmDeleteDialog->enterModalState(true, juce::ModalCallbackFunction::create([this, confirmDeleteDialog](int result) {
                if (result == 1) // User confirmed deletion
                {
                    presetManager.deletePreset(presetManager.getCurrentPreset());
                    loadPresetList();
                }
                delete confirmDeleteDialog;
            }), true);
        }
        if (button == &restoreDefaultsButton)
        {
            //presetManager.restoreDefaults();  Use the new method
            loadPresetList();
        }

    }
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override
    {
        if (comboBoxThatHasChanged == &presetList)
        {
            presetManager.loadPreset(presetList.getItemText(presetList.getSelectedItemIndex()));
        }
    }

    void configureButton(juce::Button& button, const juce::String& buttonText)
    {
        button.setButtonText(buttonText);
        button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
        addAndMakeVisible(button);
        button.addListener(this);
    }

    void loadPresetList()
    {
        presetList.clear(juce::dontSendNotification);
        const auto allPresets = presetManager.getAllPresets();
        const auto currentPreset = presetManager.getCurrentPreset();
        presetList.addItemList(allPresets, 1);
        presetList.setSelectedItemIndex(allPresets.indexOf(currentPreset), juce::dontSendNotification);
    }
    // separate out warning windows

    PresetManager& presetManager;
    juce::TextButton saveButton, deleteButton, previousPresetButton, nextPresetButton, restoreDefaultsButton;
    juce::ComboBox presetList;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetPanel)
};
