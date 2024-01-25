# JUCE ROMpler Template: Hello ROMpler!

This repository contains a template for creating a ROMpler using the JUCE framework. A ROMpler is a type of electronic music instrument that plays audio samples (ROM) based on MIDI input. This template is designed to help you get started with building your own ROMpler in JUCE, providing the necessary groundwork and example code.

## ROM Folder Setup

In this version, the folder representing the ROM (`../Resources/ROM`) must be placed in the same directory where the executable is located. This allows the ROMpler to correctly locate and access the sample files.

### Code Snippet for ROM Path Resolution

In the source code, the following snippet is used to determine the path of the application directory and subsequently locate the `Resources/ROM` directory within it:

```cpp
juce::File appDirectory = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory();
juce::File romDirectory = appDirectory.getChildFile("Resources/ROM");
