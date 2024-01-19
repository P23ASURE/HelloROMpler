cmake_minimum_required(VERSION 3.15)

# Project Name and Version
project(HelloROMpler VERSION 0.0.1)

# Minimum Version
set(CMAKE_CXX_STANDARD 17)

# Add Juce's modules
add_subdirectory(JUCE)

juce_add_plugin(HelloROMpler
    # Informazioni di base sul plugin
    COMPANY_NAME "YourCompany"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE Dem0
    FORMATS Standalone VST3
    PRODUCT_NAME "Hello ROMpler")

# Plugin' Source
target_sources(HelloROMpler PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

# Headers
target_sources(HelloROMpler PRIVATE
    Source/PluginProcessor.h
    Source/PluginEditor.h)

# Used juce modeles usign: target_link_libraries
target_link_libraries(HelloROMpler PRIVATE
    # Juce Modules
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_osc
    # Optimization & Flags
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)

# Specific definitions.
target_compile_definitions(HelloROMpler
    PUBLIC
    JUCE_MODAL_LOOPS_PERMITTED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)
