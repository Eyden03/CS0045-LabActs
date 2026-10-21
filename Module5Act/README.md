# Module 5: OpenGL, GLEW, and FreeGLUT

This module contains 40 C++ OpenGL programs:

- `SourceCode/PartA/Ex01.cpp` through `Ex20.cpp`
- `SourceCode/PartB/Q01.cpp` through `Q20.cpp`
- Their results under `OutputScreenshots/PartA` and `OutputScreenshots/PartB`

## What the OpenGL libraries do

- **OpenGL** renders the graphics. Windows already provides the system OpenGL library (`opengl32`).
- **GLEW** loads modern OpenGL functions such as vertex buffer object functions.
- **FreeGLUT** creates the window and handles keyboard, mouse, display, and timer callbacks.
- **GLU** supplies older OpenGL utility functions used by some toolchains.

On Windows and Linux, the programs include GLEW before FreeGLUT:

```cpp
#include <GL/glew.h>
#include <GL/glut.h>
```

Do not reverse that order. GLEW must be included before other OpenGL headers.

## Recommended Windows setup: MSYS2 MinGW-w64 + VS Code

This is the closest reproducible setup to the MinGW environment used to create these activities. Do not download random individual DLL or header files from third-party websites; install one matching toolchain so the compiler, headers, libraries, and DLLs use the same architecture.

### 1. Install the tools

1. Install [MSYS2](https://www.msys2.org/).
2. Open the **MSYS2 UCRT64** terminal.
3. Update MSYS2:

   ```bash
   pacman -Syu
   ```

   If MSYS2 asks you to close the terminal, reopen **MSYS2 UCRT64** and run the command again.

4. Install the compiler, debugger, CMake, GLEW, and FreeGLUT:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-glew mingw-w64-ucrt-x86_64-freeglut
   ```

5. Add `C:\msys64\ucrt64\bin` to the Windows `Path` environment variable, then restart VS Code.
6. Install the VS Code **C/C++** extension by Microsoft.

Check the installation in a new VS Code terminal:

```powershell
g++ --version
cmake --version
```

### 2. Build one activity directly

From the `Module5Act` directory, create a build-output folder and compile an activity:

```powershell
New-Item -ItemType Directory -Force bin | Out-Null
g++ .\SourceCode\PartB\Q20.cpp -std=c++17 -o .\bin\Q20.exe -lglew32 -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
.\bin\Q20.exe
```

Replace `Q20.cpp` and `Q20.exe` with the activity you want to build. If the compiler reports undefined references, keep all `-l...` linker options after the `.cpp` source file.

### 3. Build from VS Code with `Ctrl+Shift+B`

Create `.vscode/tasks.json` in your cloned repository and use this task:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "cppbuild",
      "label": "Build active OpenGL file",
      "command": "C:\\msys64\\ucrt64\\bin\\g++.exe",
      "args": [
        "-std=c++17",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}\\${fileBasenameNoExtension}.exe",
        "-lglew32",
        "-lfreeglut",
        "-lopengl32",
        "-lglu32",
        "-lwinmm",
        "-lgdi32"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```

Open the desired `.cpp` file, press `Ctrl+Shift+B`, and run the `.exe` created beside that source file.

## Build every activity with CMake

The included `CMakeLists.txt` creates a separate executable for every Part A and Part B source file.

Using the MSYS2 UCRT64 toolchain:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
cmake --build build
```

The executables are placed in:

```text
build/bin/PartA
build/bin/PartB
```

For example:

```powershell
.\build\bin\PartB\PartB_Q20.exe
```

To build only one activity:

```powershell
cmake --build build --target PartB_Q20
```

## Alternative Windows setup: Visual Studio + vcpkg

Install Visual Studio Build Tools with the **Desktop development with C++** workload, CMake, Git, and [vcpkg](https://learn.microsoft.com/vcpkg/get_started/get-started). The included `vcpkg.json` declares GLEW and FreeGLUT.

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release
.\build\bin\PartB\Release\PartB_Q20.exe
```

Use either the MSYS2/MinGW method or the Visual Studio/vcpkg method consistently. Do not mix 32-bit libraries, 64-bit libraries, MinGW libraries, and Visual Studio libraries.

## Linux

Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake libglew-dev freeglut3-dev
cmake -S . -B build
cmake --build build -j
./build/bin/PartB/PartB_Q20
```

## macOS

The source files use the system OpenGL and GLUT frameworks on macOS, so GLEW is not required:

```bash
xcode-select --install
brew install cmake
cmake -S . -B build
cmake --build build -j
./build/bin/PartB/PartB_Q20
```

Apple has deprecated OpenGL, but it remains sufficient for these compatibility-profile laboratory exercises.

## Common setup errors

### `fatal error: GL/glew.h: No such file or directory`

GLEW is not installed for the compiler being used, or VS Code is calling a different `g++`. Run `where.exe g++` and verify that it resolves to `C:\msys64\ucrt64\bin\g++.exe`.

### `fatal error: GL/glut.h: No such file or directory`

FreeGLUT is missing from the active toolchain. Install the UCRT64 FreeGLUT package shown above.

### `undefined reference to ...`

Check that the linker flags appear after the source file and include:

```text
-lglew32 -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
```

### `freeglut.dll was not found` or `glew32.dll was not found`

Add `C:\msys64\ucrt64\bin` to `Path`, or copy the required DLLs from that directory beside the generated `.exe`. Do not use DLLs from a different architecture or compiler distribution.

### The program opens and immediately closes

Run the executable from a terminal so error messages remain visible. Most activities enter `glutMainLoop()` and stay open until the window is closed; activities with an Escape-key handler can also be closed with **Esc**.

### Black window or unsupported OpenGL behavior

Update the graphics driver supplied by Intel, AMD, or NVIDIA. These exercises use legacy/compatibility OpenGL features, so a compatibility-capable desktop driver is required.
