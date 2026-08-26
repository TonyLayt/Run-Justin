# Run Justin

Run Justin is a small 2D action runner built with C++ and SFML. Justin runs through a cemetery, jumps over obstacles and fights zombies. The longer a run lasts, the faster the game becomes. The goal is to survive and defeat as many enemies as possible.

## Download

The ready-to-play Windows version is available on the [Releases page](https://github.com/TonyLayt/Run-Justin/releases/latest).

Download `Run-Justin-Windows-x64.zip`, extract it and run `Run-Justin.exe`. Visual Studio is not required.

The game is built for Windows 10/11 x64. If a Microsoft runtime DLL is missing, the [Microsoft Visual C++ Redistributable x64](https://aka.ms/vs/17/release/vc_redist.x64.exe) is required.

## Controls

| Action | Control |
| --- | --- |
| Start / menu buttons | Left mouse button |
| Jump | `Space` |
| Attack | Left mouse button |
| Pause / resume | `Esc` |

## What's in the game

- Player and enemy animations
- Jumping, melee attacks and collision handling
- Enemy spawning and respawning
- Kill counter and game-over statistics
- Title, loading, pause and game-over screens
- Increasing game speed over time
- Scrolling platforms and a parallax background
- Background music and sound effects
- TMX level data loading with TinyXML

## Built with

- C++17
- SFML 2.6.1
- TinyXML
- Visual Studio 2022

## Building from source

The project was developed in Visual Studio 2022. A local build requires an x64 C++ project with the repository source files (including `lib/*.cpp` and `Run-Justin.rc`), C++17 enabled, and the SFML `include` and `lib` directories configured.

The Release configuration uses:

```text
sfml-main.lib
sfml-graphics.lib
sfml-window.lib
sfml-audio.lib
sfml-system.lib
```

The subsystem is set to `Windows (/SUBSYSTEM:WINDOWS)`. The SFML release DLL files and `openal32.dll` must be placed next to the executable.

## About the project

The game began as an SFML learning project and was gradually expanded with additional gameplay systems, enemies, animations, audio, menus, pause handling and a kill counter. The current Windows build is playable from the title screen through game over.

The repository focuses on programming and game integration. Visual and audio assets are external resources and are not presented as original artwork.
