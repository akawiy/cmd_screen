<img width="1480" height="940" alt="banner" src="https://github.com/user-attachments/assets/f47045e4-5bba-4ade-be1c-aea1e81991f0" />

# 📺 CMD Screen

This is a program that can:
- print images
- play videos
- show live camera picture

directly in command prompt

## 🔨 Build (Windows)

1. Make sure you have the latest version of [OpenCV](https://opencv.org) installed at `C:\tools\opencv` (or you can edit the path in `CMakeLists.txt`)
2. Download the latest version of the project ([v2.0.1.zip](https://github.com/akawiy/cmd_screen/archive/refs/tags/v2.0.1.zip))
3. Unpack the ZIP archive
4. Compile the project into a single executable
     - Using [JetBrains CLion](https://jetbrains.com/clion) (easier, recommended)
     - Using [CMake](https://cmake.org)

## 📋 Usage (Windows)

Once you have `cmd_screen.exe` (you can download it [here](https://github.com/akawiy/cmd_screen/releases/download/v2.0.1/cmd_screen.exe)), 
open the terminal that supports ANSI 24-bit Truecolor codes (almost all modern terminals do) in the same directory and use one of the following commands:

### Print image:
```bash
cmd_screen img <image path>
```

### Play video right away:
```bash
cmd_screen vid <video path>
```
- _Pros: no need to wait for preloading to finish, no risk of RAM overflow, adaptive sizing and centering_
- _Cons: lower framerate, worse quality_

### Play video after preloading:
```bash
cmd_screen vid <video path> preload
```
- _Pros: higher framerate, better quality_
- _Cons: high risk of RAM overflow for 1min+ videos, no adaptive sizing and centering_

### Show live picture from specific camera:
```bash
cmd_screen cam <camera index>
```
_index should be a non-negative integer_

### Show live picture from default camera:
```bash
cmd_screen cam
```
_the same as `cmd_screen cam 0`_

**Not vibecoded and made with ❤️ by Vladimir Polischuk**
