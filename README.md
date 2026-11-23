# CorelCraft

CorelCraft is an independent C++ vector graphics application prototype. It is not affiliated with Corel Corporation or CorelDRAW.

## Technology
- C++20
- Qt 6 Widgets
- Qt Graphics View / Qt Painter
- Qt SVG
- PDF export with Qt QPdfWriter
- Dedicated CDR adapter boundary (CDR parsing is not implemented yet)
- CMake, Git and GitHub

## Phase 1
- Dark desktop UI and A4-like artboard
- Rectangle, ellipse and text insertion
- Selection, movement, deletion and colour selection
- Mouse-wheel zoom
- SVG import as one object and SVG export
- PDF export

## Build on Windows 11
Install Visual Studio 2022 Community with Desktop development with C++, Qt 6 for MSVC 2022 64-bit (Widgets, Svg, SvgWidgets), CMake and Git.

Run in Developer PowerShell for VS 2022 (adjust the Qt path):
```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:\Qt\6.8.3\msvc2022_64"
cmake --build build --config Release
.\build\Release\CorelCraft.exe
```

## Limitations
This is an early foundation, not a professional vector editor yet. CDR import/export, native project save/open, undo/redo, editable imported SVG paths, Bezier/node editing, CMYK colour management, bleed, font embedding and print preflight are future work.

## CDR roadmap
The CDR adapter will be isolated in `src/io/CdrIO.*`. We plan to evaluate an open-source reader such as libcdr against legally obtained sample files. No full CDR compatibility is claimed.

## License
No project license has been selected yet. Third-party dependencies and sample files retain their own licenses.
