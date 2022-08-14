# Helios Game Environment [![License](https://img.shields.io/github/license/pernicius/Helios.svg)](https://github.com/pernicius/Helios/blob/main/LICENSE.md)

Inspired by [Eve Online](https://www.eveonline.com/), Helios will try to implement multiple tools and applications to realize a similar system. The plan is to set little goals on the way to a complete toolset. Currently there is not much implemented, however we have a big goal and the way is the project.

## Getting started
Currently the main development is done with Visual Studio 2022. The focus target is Windows with Linux and MacOS in mind.

### 1.Downloading the repository
To begin with, clone the repository with:<br>
`git clone --recursive https://github.com/pernicius/Helios`<br>
If the repository was cloned non-recursively, or for some reason the submodules where not downloaded, use:<br>
`git submodule update --init`<br>
to clone all the necessary modules.

### 2. Configuring the Workspace
After the first cloning and when ever files are moved, renamed, added or deleted you must regenerate the Workspace and Project files with:<br>
`cd scripts\\windows` and `generate_workspace.bat`<br>
That will generate all necesarry files for Visual Studio. Helios uses [Premake](https://premake.github.io/) for simple build configuration so the later goal is to support multiple tools across Windows, Linux and MacOS. 

## The Big Target
Because i use the [Youtube series](https://thecherno.com/engine) from [TheCherno](https://www.youtube.com/user/TheChernoProject) about his Game Engine to learn more C++ and rendering stuff, the development is rather slow.

### Long term goals:
- [ ] An environment to setup a server (or group of servers)
- [ ] Toolset to control the server environment
- [ ] Toolset to edit the world and models
- [ ] A multi platform game client

### Short term goals:
- [ ] A working multi platform 3D engine with native rendering API support
  - [ ] Windows *(OpenGL, Vulkan, DirectX)*
  - [ ] Linux *(OpenGL, Vulkan)*
  - [ ] MacOS *(OpenGL, Metal)*
- [ ] A working model/scene editor
- [ ] Complete documentation
