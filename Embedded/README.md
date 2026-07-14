# Embedded

> Program microcontrollers, set up networking with vision system and AI.

---

## Overview

**Responsibilities**
- Program STM32 microcontroller
- Motor and Kicker Control
- Receive and Process AI commands
- Process Sensor Data

---

## GitHub Actions CI: Build TritonBots-2027 STM32 Firmware

This workflow builds the Embedded/STM32H723ZG_nucleo STM32 firmware on `ubuntu-latest` using CMake + Ninja and the Arm GNU toolchain (`arm-none-eabi-gcc`). It also adds extra diagnostics to help debug failures related to the CMake toolchain file path.

---

**Pipeline steps**
- **Checkout** the repo with full history (`actions/checkout@v4`, `fetch-depth: 0`).
- **Install dependencies**:
  - `cmake`
  - `ninja-build`
  - `gcc-arm-none-eabi`
  - `binutils-arm-none-eabi`
- **Check tools** and list the toolchain directory: `Embedded/STM32H723ZG_nucleo/cmake`.
- **Debug repository contents** (pwd, git ref/status, workspace listings) and confirm the toolchain file exists:
  - `Embedded/STM32H723ZG_nucleo/cmake/gcc-arm-none-eabi.cmake`
  - (also checks it via `git ls-files`)
- **Configure CMake** using Ninja and passes the toolchain file using an absolute path:
  - `-DCMAKE_TOOLCHAIN_FILE="$PWD/Embedded/STM32H723ZG_nucleo/cmake/gcc-arm-none-eabi.cmake"`
- **Build firmware** with:
  - `cmake --build Embedded/STM32H723ZG_nucleo/build --parallel`
- **Upload artifacts** as `TritonBots-2027-firmware` (matching `*.elf`, `*.hex`, `*.bin`, `*.map`) from `Embedded/STM32H723ZG_nucleo/build/`.

---

## Folder Structure

```plaintext
.
├── docs/           # Documentation
├── src/            # Source code, CAD, firmware, etc.
├── tests/          # Tests, validation, simulations
├── scripts/        # Utility scripts
├── assets/         # Images, diagrams, models
└── README.md
```

Modify this structure as needed for your team.

---

## Getting Started

### Prerequisites

Before building, ensure the following tools are installed on your system:

| Tool | Purpose | Install |
|------|---------|---------|
| `arm-none-eabi-gcc` | ARM cross-compiler | See platform instructions below |
| `cmake` (≥ 3.22) | Build system generator | [cmake.org](https://cmake.org/download/) |
| `ninja` | Build executor | See platform instructions below |
| `git` | Version control | [git-scm.com](https://git-scm.com/) |
| STM32 VS Code Extension | Flash & debug | VS Code Marketplace |
| `moteus_gui` | Motor controller GUI | mjbots release page |
| mjcanfd-usb-1x adapter | CAN-FD USB interface | mjbots hardware |

#### 🪟 Windows

Install via [MSYS2](https://www.msys2.org/) (recommended):

```powershell
# In an MSYS2 MinGW64 terminal:
pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-ninja

# Verify installations — run these in PowerShell after adding MSYS2 to PATH:
arm-none-eabi-gcc --version
cmake --version
ninja --version
```plaintext

> ⚠️ Make sure `C:\msys64\mingw64\bin` is on your system **PATH** so PowerShell
> can find `arm-none-eabi-gcc.exe` and `ninja.exe`.

#### 🐧 Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install cmake ninja-build gcc-arm-none-eabi binutils-arm-none-eabi

# Verify:
arm-none-eabi-gcc --version
cmake --version
ninja --version
```plaintext

#### 🍎 macOS

```bash
brew install cmake ninja
brew install --cask gcc-arm-embedded

# Verify:
arm-none-eabi-gcc --version
cmake --version
ninja --version
```plaintext

---

## Build Instructions

### First-Time Setup (New Users)

1. **Clone the repository:**

```bash
git clone <repository-url>
cd TritonBots-2027
```plaintext

2. **Navigate to the STM32 project:**

```bash
cd Embedded/STM32H723ZG_nucleo
```plaintext

3. **Configure the build with the ARM toolchain:**

```bash
# Linux / macOS
cmake -B build -S . \
  -G "Ninja" \
  -DCMAKE_TOOLCHAIN_FILE="cmake/gcc-arm-none-eabi.cmake" \
  -DCMAKE_BUILD_TYPE=Debug
```plaintext

```powershell
# Windows (PowerShell) — use backslashes and quotes
cmake -B build -S . `
  -G "Ninja" `
  -DCMAKE_TOOLCHAIN_FILE="cmake\gcc-arm-none-eabi.cmake" `
  -DCMAKE_BUILD_TYPE=Debug
```plaintext

> ✅ You should see `arm-none-eabi-gcc` detected as the C compiler. If you
> see `cc.exe` or your system's native GCC instead, the toolchain file was
> not picked up — double-check your PATH and the command above.

4. **Build the firmware:**

```bash
cmake --build build --parallel
```plaintext

5. **Locate the output artifacts** in `build/`:

| File | Description |
|------|-------------|
| `STM32H723ZG_nucleo.elf` | Flashable ELF binary |
| `STM32H723ZG_nucleo.hex` | Intel HEX format |
| `STM32H723ZG_nucleo.bin` | Raw binary |
| `STM32H723ZG_nucleo.map` | Linker map file |

---

### Rebuilding (Returning Users)

If you've already configured the build before, simply rebuild:

```bash
cd Embedded/STM32H723ZG_nucleo
cmake --build build --parallel
```plaintext

---

### Clean Rebuild

If you encounter stale cache issues, toolchain errors, or suspect a corrupted
build directory, do a full clean rebuild:

```bash
# Linux / macOS
cd Embedded/STM32H723ZG_nucleo
rm -rf build/
cmake -B build -S . \
  -G "Ninja" \
  -DCMAKE_TOOLCHAIN_FILE="cmake/gcc-arm-none-eabi.cmake" \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```plaintext

```powershell
# Windows (PowerShell)
cd Embedded\STM32H723ZG_nucleo
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
cmake -B build -S . `
  -G "Ninja" `
  -DCMAKE_TOOLCHAIN_FILE="cmake\gcc-arm-none-eabi.cmake" `
  -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```plaintext

> ⚠️ A clean rebuild is **required** any time you switch build types (Debug ↔
> Release), change the toolchain file, or after pulling changes that modify
> `CMakeLists.txt` or `cmake/stm32cubemx/CMakeLists.txt`.

---

### Release Build

```bash
cmake -B build -S . \
  -G "Ninja" \
  -DCMAKE_TOOLCHAIN_FILE="cmake/gcc-arm-none-eabi.cmake" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```plaintext

---

### Building in VS Code

If you prefer an IDE workflow over the command line:

1. Open **`Embedded/STM32H723ZG_nucleo`** in VS Code (File → Open Folder).

> ⚠️ Open this specific folder — not the repo root. The STM32 VS Code
> Extension requires the project root to be `STM32H723ZG_nucleo/` so it
> can find the CMake, OpenOCD, and launch configurations.

2. When prompted, select **GCC ARM** as the CMake kit, or configure the
   extension to use `cmake/gcc-arm-none-eabi.cmake` as the toolchain file.
3. Use the STM32 extension's **Build**, **Flash**, and **Debug** controls
   from the activity bar.

---

### Troubleshooting

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| `cc.exe` used instead of `arm-none-eabi-gcc` | Wrong compiler cached in build dir | Delete `build/` and reconfigure with toolchain file |
| `Could not find toolchain file` | Path separator issue on Windows | Use backslashes: `"cmake\gcc-arm-none-eabi.cmake"` |
| `ninja: command not found` | Ninja not on PATH | Install ninja and ensure it's on PATH |
| `undefined reference to moteus_*` | Driver `.c` files missing from `target_sources` | Add source files to `CMakeLists.txt` |
| `not a directory` warnings on headers | `.h` files passed to `target_include_directories` | Pass directory paths only (e.g. `Core/Inc`) |
| `Unsupported STM32 family` error in `stm32_hal.h` | Device macro not matched | Ensure `STM32H723xx` is in `MX_Defines_Syms` in `cmake/stm32cubemx/CMakeLists.txt` |
| `.thumb` / `.thumb_set` assembler errors | Native GCC used instead of ARM cross-compiler | Verify `arm-none-eabi-gcc` is on PATH and toolchain file is passed |

---

## Development Workflow

### STM32: Run & Debug in VS Code

To run and debug the STM32 firmware using the **STM32 VS Code Extension**, you must open the project folder in VS Code:

1. Open **`Embedded/STM32H723ZG_nucleo`** in VS Code (File → Open Folder).
2. Use the STM32 extension's Run/Debug controls.

> Important: Opening only subfolders (e.g. `Core/`) may prevent the extension
> from finding the correct build/openocd/launch configuration.

### Branch Workflow

1. Create a feature branch.
2. Make your changes.
3. Test your work.
4. Update documentation if needed.
5. Submit a pull request.

---

## Coding & Design Standards

- K&R Style
- camelCase for most functions and variables
- SCREAMING_SNAKE_CASE for `#define` consts
- PascalCase for classes and structs
- Doxygen comments
- Put a README in each top-level folder

---

## Testing

Explain how to verify changes.

```bash
# Example commands
```plaintext

Include any hardware validation or simulation steps if applicable.

---

## Documentation

Keep documentation up to date for:

- Architecture
- Interfaces
- Design decisions
- Hardware or software dependencies
- Troubleshooting

Store larger documents in the `docs/` directory.

---

## Interfaces

Document what this team provides to or requires from other teams.

### Inputs

- AI Commands enter the Radio Base Station
- Mechanical specifications and dimensions
- Electrical limits for motors

### Outputs

- Motor and Kicker actuation for Mechanical and Electrical Feedback
- Robot motion for AI
- Sensor data for AI and Electrical

### Dependencies

- AI
- Electrical
- Mechanical

---

## Important Files

| File/Folder | Purpose |
|-------------|---------|
| `Embedded/STM32H723ZG_nucleo/` | STM32 firmware project root |
| `Embedded/STM32H723ZG_nucleo/Core/Src/` | Application source files |
| `Embedded/STM32H723ZG_nucleo/Core/Inc/` | Application header files |
| `Embedded/STM32H723ZG_nucleo/cmake/gcc-arm-none-eabi.cmake` | ARM cross-compiler toolchain definition |
| `Embedded/STM32H723ZG_nucleo/cmake/stm32cubemx/` | STM32CubeMX-generated CMake config |
| `Embedded/STM32H723ZG_nucleo/STM32H723xG_flash.ld` | Linker script |
| `docs/` | Documentation |
| `tests/` | Validation and testing |
| `scripts/` | Automation utilities |

---

## Current Priorities

- [ ] Task 1
- [ ] Task 2
- [ ] Task 3

---

## Future Improvements

- Improvement 1
- Improvement 2
- Improvement 3

---

## Maintainers

| Name | Role |
|------|------|
| Sukhjeet Sekhon | Team Lead |
| TBD | Developer |

---

## Related Documentation

- Root repository README
- Team design documents
- Project roadmap
- Hardware documentation