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

This workflow builds the Embedded/TritonBots-2027 STM32 firmware on `ubuntu-latest` using CMake + Ninja and the Arm GNU toolchain (`arm-none-eabi-gcc`). It also adds extra diagnostics to help debug failures related to the CMake toolchain file path.

---

**Pipeline steps**
- **Checkout** the repo with full history (`actions/checkout@v4`, `fetch-depth: 0`).
- **Install dependencies**:
  - `cmake`
  - `ninja-build`
  - `gcc-arm-none-eabi`
  - `binutils-arm-none-eabi`
- **Check tools** and list the toolchain directory: `Embedded/TritonBots-2027/cmake`.
- **Debug repository contents** (pwd, git ref/status, workspace listings) and confirm the toolchain file exists:
  - `Embedded/TritonBots-2027/cmake/gcc-arm-none-eabi.cmake`
  - (also checks it via `git ls-files`)
- **Configure CMake** using Ninja and passes the toolchain file using an absolute path:
  - `-DCMAKE_TOOLCHAIN_FILE="$PWD/Embedded/TritonBots-2027/cmake/gcc-arm-none-eabi.cmake"`
- **Build firmware** with:
  - `cmake --build Embedded/TritonBots-2027/build --parallel`
- **Upload artifacts** as `TritonBots-2027-firmware` (matching `*.elf`, `*.hex`, `*.bin`, `*.map`) from `Embedded/TritonBots-2027/build/`.

---


## Folder Structure

```text
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

- moteus_gui
- mjcanfd-usb-1x adapter
- STM32 for VS Code Extension

### Setup

```bash
# Example
git clone <repository>
cd <team-folder>

# Additional setup commands
```

---

## Development Workflow

## STM32: Run & Debug in VS Code


To run and debug the STM32 firmware using the **STM32 VS Code Extension**, you must open the project folder in VS Code:

1. Open **`Embedded/TritonBots-2027`** in VS Code (File → Open Folder).
2. Use the STM32 extension’s Run/Debug controls.

> Important: Opening only subfolders (e.g. `Core/`) may prevent the extension from finding the correct build/openocd/launch configuration.



1. Create a feature branch.
2. Make your changes.
3. Test your work.
4. Update documentation if needed.
5. Submit a pull request.

---

## Coding & Design Standards

- K&R Style
- camelCase for most functions and variables
- SCREAMING_SNAKE_CASE for #define consts
- PascalCase for classes and structs
- Doxygen comments
- Put a README in each top-level folder

---

## Testing

Explain how to verify changes.

```bash
# Example commands
```

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
| `src/` | Primary implementation |
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