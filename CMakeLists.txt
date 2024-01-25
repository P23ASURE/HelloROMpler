cmake_minimum_required(VERSION 3.15)

project(HelloROMpler)

# If you've installed JUCE somewhere, you might need to specify its path here
set(JUCE_DIR "../JUCE")

# If JUCE is not a subdirectory of your project, you'll need to find it
find_package(JUCE CONFIG REQUIRED
    COMPONENTS 
    juce_audio_basics
    juce_audio_devices
    juce_audio_formats
    juce_audio_plugin_client
    juce_audio_processors
    juce_audio_utils
    juce_core
    juce_data_structures
    juce_dsp
    juce_events
    juce_graphics
    juce_gui_basics
    juce_gui_extra
    juce_osc
)

juce_add_plugin("HelloROMpler"
    # VERSION ... # Set this if you want
    COMPANY_NAME "YourCompanyName"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE JucePlugin_ManufacturerCode
    PLUGIN_CODE JucePlugin_PluginCode
    FORMATS VST3 Standalone
    PRODUCT_NAME "HelloROMpler")

target_sources(HelloROMpler
    PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/ADSRComponent.cpp
    Source/ADSRComponent.h)

target_compile_definitions(HelloROMpler
    PRIVATE
    JUCE_MODAL_LOOPS_PERMITTED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)

target_link_libraries(HelloROMpler
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_osc
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags)

