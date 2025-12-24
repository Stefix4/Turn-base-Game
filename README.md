# Turn-base-Game
Game made using Raylib and C++

#### **How to compile & run:**

• Clone repository using:
```bash
git clone https://github.com/Stefix4/Turn-base-Game.git
```

## Building & Running (cross-platform) ✅

**Prerequisites**
- Linux: a working build toolchain (g++) and Raylib (dev package or static/lib files in `lib/`).
- Windows: use **MSYS2 (MinGW64)** — install the toolchain and raylib packages in the MinGW64 shell:
```bash
# In MSYS2 MinGW64 shell
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-raylib
```

**Build**
```bash
# Build for your current platform (auto-detected)
make

# Force Windows build from any shell if needed
make WINDOWS=1
```

**Run**
```bash
make run
```

**Clean**
```bash
make clean
```

**Help**
```bash
make help
```

> Note: On Windows, do not place runtime DLLs (`libgcc_s_seh-1.dll`, `libwinpthread-1.dll`, etc.) in the project root — they can interfere with the compiler. Keep them in your system `/mingw64/bin` or in a dedicated `dist/` folder for distribution. If you see silent compiler failures, check for stray DLLs in the repo root and move them out of the way (e.g., `lib/_backup_dlls/`).

**Tips**
- The `Makefile` compiles sources into `build/windows/` or `build/linux/` and links against `lib/`. If you prefer a debug build, set `CXXFLAGS += -g -Og` on the command line or modify the `Makefile`.

## Troubleshooting ⚠️

- Compiler silently fails or `make` exits with code 1:
  - Check for stray runtime DLLs in the project root (e.g., `libgcc_s_seh-1.dll`, `libwinpthread-1.dll`). Move them out of the repo root (example: `mkdir -p lib/_backup_dlls && mv libgcc_s_seh-1.dll libwinpthread-1.dll lib/_backup_dlls/`).
  - Reinstall the MSYS2 toolchain if needed: `pacman -S --needed mingw-w64-x86_64-gcc`
  - Re-run `make clean` then `make` and inspect compiler output.

- Linker errors / missing raylib:
  - Ensure Raylib dev files or static library are available (`lib/libraylib.a` or system raylib package).
  - On Linux: install `libraylib-dev` (or equivalent) via your package manager.
  - Verify `ls lib/` and `nm -A lib/libraylib.a | head` to inspect the archive.

- Graphics or runtime issues:
  - Run `make run` in the same shell used for build (MSYS2 MinGW64 if on Windows).
  - Ensure GPU drivers support the OpenGL version printed by raylib at startup.

- Useful debug commands:
  - `make -n` (show commands without running)
  - `make clean && make V=1` or run the g++ link command shown by `make -n` directly to capture full error output

## Windows checklist 🪟

If you're building on Windows (MSYS2 / MinGW64), check these if things fail:
- Use the **MinGW64** shell (MSYS2) — building from other shells can pick wrong toolchains.
- Ensure raylib and the toolchain are installed in MinGW64 (`pacman -S mingw-w64-x86_64-raylib mingw-w64-x86_64-gcc`).
- Do not keep runtime DLLs in the project root; place them in `/mingw64/bin` or `dist/`.
- If you see silent compiler failures, move any suspicious DLLs out of the repo root and retry.

## Contributing 🤝

Contributions are welcome! If you want to contribute:
- Open an issue first to discuss larger changes.
- Create a branch, make small, focused commits, and submit a pull request.
- Run `make` and `make run` locally to verify changes and include build notes in the PR description if the change requires extra steps.

![image](https://github.com/Stefix4/Turn-base-Game/assets/94927709/df2e3525-7f3c-45f3-bdca-a3c2333ead51)
