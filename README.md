# Beam
A fairly simple raytracing framework.

## Setup
All commands should be run from the root folder (the folder that contains this
README file) unless otherwise specified.
You may also have to replace `/` in paths with `\` depending on your platform
and shell.

### Prerequisites
* [Premake](https://premake.github.io/)
* Some way to build C++ projects, such as g++ and GNU Make or Visual Studio.

### Building
To generate the project files, run:

    premake5 [action]

where `[action]` corresponds to your build environment;
see [the Premake documentation](https://premake.github.io/docs/Using-Premake)
for a list of supported actions.

After generating the project files, use them as you would normally with your
build environment.
If you are using Make, you can run the command

    make help

to see how to build different configurations.

There is currently an issue where the `gmake2` action doesn't create the
output folders, and building will fail.
If this happens, for now you can manually create these folders with:

    mkdir -p _out/bin/debug-x86_64
    mkdir -p _out/bin/profile-x86_64
    mkdir -p _out/bin/release-x86_64
    mkdir -p _out/obj/debug-x86_64
    mkdir -p _out/obj/profile-x86_64
    mkdir -p _out/obj/release-x86_64

### Running
The executable gets generated as `_out/bin/<config>/beam/beam`.
The `<config>` depends on the build configuration.
You need to pass a scene file as a command line argument; one is provided as
`scene.json` in the root folder.
For example, to run the following command to run the release build (after
building it) with the provided scene file:

    ./_out/bin/release-x86_64/beam/beam scene.json
