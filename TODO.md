# TODO - Debug GitHub Actions CI for STM32CubeMX CMake

- [ ] Update `.github/workflows/build.yml` to add stronger post-checkout diagnostics (pwd, git ref/status, ls/test for toolchain file).
- [ ] Update workflow to pass `-DCMAKE_TOOLCHAIN_FILE` using an absolute path (`$PWD/...`).
- [ ] Re-run CI to confirm CMake configure finds the toolchain file and Ninja is available.
- [ ] If still failing, add diagnostics for sparse checkout/submodules and verify correct branch/commit.

