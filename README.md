# Cloning the repo
`git clone https://github.com/caveman250/SparkTestProject --recurse-submodules`

# Required Software
- Python
- Cmake
- OpenGL (Windows and Linux)
- Visual Studio 2022 (Windows)
- Xcode (Mac)
- gcc/g++ (Linux)
- SDL2 (Linux)

# Building
## CLion
1. Open the project directory in CLion.
2. When prompted to set up initial profiles, you should see the following presets available for your platform:
   - Debug
   - Debug Editor
   - Release
   - Release Editor
   - Distribution
   - Distribution Editor
3. Enable all the presets.
4. Set your configuration to "TestProject".
5. Select your desired Profile.
6. Build run and debug as normal.

## Visual Studio / Rider (Windows only)
1. Run GenerateVSProject.bat from the repo root.
2. Navigate to projects/vs
3. Open Spark.sln
4. Set "TestProject" as the startup project
5. Select your desired build type, you should see the following options:
   - Debug
   - DebugEditor
   - Release
   - ReleaseEditor
   - Distribution
   - DistributionEditor
6. Build run and debug as normal.
7. Rerun GenerateVSProject.bat every time you add new files.

## Xcode
1. Run GenerateXcodeProject.sh from the repo root.
2. Navigate to projects/xcode
3. Open Spark.xcodeproj
4. Set "TestProject" as your target
5. Under your target, click "Edit Scheme" and select your desired build type, you should see the following options:
    - Debug
    - DebugEditor
    - Release
    - ReleaseEditor
    - Distribution
    - DistributionEditor
6. Build run and debug as normal.
7. Rerun GenerateXcodeProject.sh every time you add new files.

## CLI
1. generate the build files for a given config with: `cmake --preset "Preset Name"`
   - The available presets are:
      - Debug (`<platform>`)
      - Debug Editor (`<platform>`)
      - Release (`<platform>`)
      - Release Editor (`<platform>`)
      - Distribution (`<platform>`)
      - Distribution Editor (`<platform>`)
   - Where `<platform>` is one of:
      - Windows
      - Mac
      - Linux
   - eg: `cmake --preset "Debug Editor (Windows)"`
   - This will generate one of the following folders:
     - `projects/<generator>/debug`
     - `projects/<generator>/debug_editor`
     - `projects/<generator>/release`
     - `projects/<generator>/release_editor`
     - `projects/<generator>/distribution`
     - `projects/<generator>/distribution_editor`
   - Where `<generator>` is one of:
     - Windows: `Ninja`
     - Mac: `Unix Makefiles`
     - Linux: `Unix Makefiles`
2. Navigate to your generated directory from step 1.
3. Run `cmake --build . --target TestProject --parallel <num desired threads>`
4. An executable will output to:
   - Windows: `projects/<generator>/<config>/app/TestProject.exe`
   - Mac: `projects/<generator>/<config>/app/TestProject.app`
   - Linux: `projects/<generator>/<config>/app/TestProject`
   
# Additional Debugging Visualisers
Spark provides some additional debugger scripts to help view certain types in the debugger. Should you wish to use these follow the instructions for your platform.
## Windows
No additional debugging scripts at this time.
## Mac
Add the following to your ~/.lldbinit
````
command script import <path to repo>/Spark/debug/lldb/lldb_init.py
````
## Linux
Add the following to your ~/.gdbinit
```
set auto-load safe-path <path to repo>
```

