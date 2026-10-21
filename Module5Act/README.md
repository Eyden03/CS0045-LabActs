# Module 5 Laboratory Activities

This folder contains the source code and output screenshots for Module 5. Part A uses `Ex01` through `Ex20`; Part B uses `Q01` through `Q20`.

## Requirements

- A C++ compiler with C++11 support
- CMake 3.21 or newer
- OpenGL
- GLEW and FreeGLUT (macOS uses its system OpenGL/GLUT frameworks and does not need GLEW)

The repository does not include a compiler or prebuilt OpenGL binaries. Install the dependencies using one of the options below.

### Windows (recommended: vcpkg)

Install Visual Studio Build Tools with the **Desktop development with C++** workload, CMake, Git, and [vcpkg](https://learn.microsoft.com/vcpkg/get_started/get-started).

From this `Module5Act` folder, configure with the vcpkg toolchain:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release
```

The included `vcpkg.json` installs GLEW and FreeGLUT automatically during configuration. If a built program reports a missing DLL, run it from the Visual Studio developer terminal or copy the corresponding vcpkg DLLs beside the executable.

### Ubuntu/Debian

```bash
sudo apt update
sudo apt install build-essential cmake libglew-dev freeglut3-dev
cmake -S . -B build
cmake --build build -j
```

### macOS

Install Xcode Command Line Tools and CMake, then run:

```bash
xcode-select --install
brew install cmake
cmake -S . -B build
cmake --build build -j
```

## Running an activity

Executables are generated under `build/bin/PartA` and `build/bin/PartB`. Target names include the part to keep similarly named exercises distinct, for example:

```powershell
.\build\bin\PartB\Release\PartB_Q20.exe
```

Single-configuration generators (such as Makefiles or Ninja) usually omit the `Release` directory.

To build only one activity, specify its target:

```powershell
cmake --build build --config Release --target PartB_Q20
```

Press **Esc** to close activities that implement an Escape-key handler; otherwise close the OpenGL window normally.
