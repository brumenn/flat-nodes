# Flat Nodes
![Unreal Engine](https://img.shields.io/badge/Unreal_Engine-4.26+-9455CE?logo=unrealengine)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/license/mit)

A minimalist style for Unreal Engine graph nodes. This plugin add a simplified visual appearance, flatter, that makes graphs clearer and more readable.

There is no impact on the performance and stability of the engine, only the visual aspect of the UI is changed : just some super tiny .png files used by Slate are replaced.

Works well on UE4 and UE5, since these files have not changed and the visual appearance of the graph nodes uses these same files.

### Features
- Graph nodes flat style
- **[New in 5.0+]** Few plugin settings : choose between gradient or true flat header - brightness control over flat header
- **[New in 5.8+]** Custom title color, header opacity, node background color and opacity in settings - brightness control over gradient header too

## Installation

### From Fab

The easiest way is to [install the plugin directly from Fab](https://www.fab.com/listings/7305134c-8f1c-46f4-aa9c-14381074aba5), like most plugins nowadays. Check the documentation [here](https://dev.epicgames.com/documentation/unreal-engine/working-with-plugins-in-unreal-engine#downloading-plugins-from-the-fab-website) if needed.

### From Github

1. In this GitHub repository, select the branch that matches your **engine version**. `main` branch is for the latest available version of the engine.
2. Click `<> Code` on the top panel then `Download ZIP`.
3. Extract the zip content in a new folder named `FlatNodes` inside the `Plugins` directory, [either in your project, or in the engine itself](https://dev.epicgames.com/documentation/en-us/unreal-engine/plugins-in-unreal-engine#pluginfolders).
4. The directory structure must match `Plugins\FlatNodes\FlatNodes.uplugin`.
5. Launch the project, the engine will attempt to compile the plugin.

> [!Note]
> Please note that I do not provide precompiled binaries at this time, so you will need to use [Visual Studio](https://visualstudio.microsoft.com/downloads/) to [compile the plugin](#build-from-sources).

## Build from sources

For Windows, you will need [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) as prerequisite.

1. Clone the source code of the plugin into the `Plugins` directory of your project (for instance `Plugins\FlatNodes`), if you haven't already done so.
2. Right-click on your project's `.uproject` file, `Generate Visual Studio project files`.
3. Either one or the other:
   - Launch the project, the engine will attempt to compile the plugin. If it fails, you may consider building inside Visual Studio.
   - Inside Visual Studio, `Reload All` and `Build Solution` in `Development Editor` mode.

### Update to a newer version of the engine

If I take too long to update the plugin when a new version is released, you can try doing it yourself, since most of the time there is hardly anything to change.

1. In an updated project working with the new version of the engine, [add the plugin](#from-github) if it isn't already added.
2. Edit `FlatNodes.uplugin` file and update the `"EngineVersion"` field to the right one.
3. Launch the project, the engine will attempt to compile the plugin. 

> [!Note]
> If it fails, it's probably because you need to use [Visual Studio](https://visualstudio.microsoft.com/downloads/) to [compile the plugin](#build-from-sources), or the new version of the engine affects the plugin more than that and some code modifications are required.

## License

The plugin is available as open source under the terms of the [MIT License](https://opensource.org/license/mit).
