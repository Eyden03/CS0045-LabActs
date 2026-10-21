# Module 5: OpenGL, GLEW, and FreeGLUT

This module contains 40 C++ OpenGL programs:

- `SourceCode/PartA/Ex01.cpp` through `Ex20.cpp`
- `SourceCode/PartB/Q01.cpp` through `Q20.cpp`
- Their results under `OutputScreenshots/PartA` and `OutputScreenshots/PartB`

## What the OpenGL libraries do

- **OpenGL** renders the graphics. Windows provides `opengl32`; macOS provides the OpenGL framework.
- **GLEW** loads modern OpenGL functions on Windows and Linux. The macOS source path uses Apple's framework directly.
- **FreeGLUT/GLUT** creates the window and handles keyboard, mouse, display, and timer callbacks. Windows uses FreeGLUT; macOS uses Apple's GLUT framework.
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

4. Install the compiler, debugger, GLEW, and FreeGLUT:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-glew mingw-w64-ucrt-x86_64-freeglut
   ```

5. Add `C:\msys64\ucrt64\bin` to the Windows `Path` environment variable, then restart VS Code.
6. Install the VS Code **C/C++** extension by Microsoft.

Check the installation in a new VS Code terminal:

```powershell
g++ --version
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

## Linux

Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential libglew-dev freeglut3-dev
mkdir -p bin
g++ SourceCode/PartB/Q20.cpp -std=c++17 -o bin/Q20 -lGLEW -lglut -lGL -lGLU
./bin/Q20
```

## Recommended macOS setup: Apple Clang + VS Code

The programs automatically select Apple's headers when `__APPLE__` is defined:

```cpp
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
```

macOS uses its built-in OpenGL and GLUT frameworks. Do not install or link the Windows FreeGLUT DLLs, and do not add GLEW to the macOS compile command.

### 1. Install the tools

1. Install the Xcode Command Line Tools:

   ```bash
   xcode-select --install
   ```

2. Confirm that Apple Clang is available:

   ```bash
   clang++ --version
   ```

3. Install Visual Studio Code and Microsoft's **C/C++** extension if you want to build from VS Code.

### 2. Build one activity directly

From the `Module5Act` directory:

```bash
mkdir -p bin
clang++ SourceCode/PartB/Q20.cpp -std=c++17 -o bin/Q20 -framework OpenGL -framework GLUT
./bin/Q20
```

Replace `Q20.cpp` and `Q20` with the desired activity. The framework options must appear in the compile command so the linker can resolve OpenGL and GLUT functions.

### 3. Build from VS Code with `Cmd+Shift+B`

Create `.vscode/tasks.json` in your cloned repository:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "cppbuild",
      "label": "Build active OpenGL file (macOS)",
      "command": "/usr/bin/clang++",
      "args": [
        "-std=c++17",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}",
        "-framework",
        "OpenGL",
        "-framework",
        "GLUT"
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

Open an activity, press `Cmd+Shift+B`, then run the generated program from the VS Code terminal.

Apple deprecated OpenGL in macOS 10.14, so the compiler may display deprecation warnings. These warnings are expected for this course's compatibility-profile exercises and do not prevent them from building.

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

### macOS reports `GL/glew.h` or `GL/glut.h` is missing

Compile with Apple Clang (`/usr/bin/clang++`) and do not manually define or remove `__APPLE__`. On macOS, the source should select `<GLUT/glut.h>` automatically; the Windows-style `<GL/...>` headers are inside the non-Apple branch.

### macOS reports undefined OpenGL or GLUT symbols

Make sure both `-framework OpenGL` and `-framework GLUT` are present after the source/output arguments.

### macOS says the developer tools are missing

Run `xcode-select --install`. If Xcode is installed but the command-line path is incorrect, select it with `sudo xcode-select --switch /Applications/Xcode.app/Contents/Developer`.

### The program opens and immediately closes

Run the executable from a terminal so error messages remain visible. Most activities enter `glutMainLoop()` and stay open until the window is closed; activities with an Escape-key handler can also be closed with **Esc**.

### Black window or unsupported OpenGL behavior

On Windows, update the graphics driver supplied by Intel, AMD, or NVIDIA. On macOS, install available macOS updates because Apple distributes its graphics drivers with the operating system. These exercises use legacy/compatibility OpenGL features.
