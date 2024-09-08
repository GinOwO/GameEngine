# GameEng
[![LICENSE](https://img.shields.io/github/license/GinOwO/GameEng?color=blue)](LICENSE) ![Language](https://img.shields.io/badge/Language-C%2B%2B-brightgreen) ![GitHub csize](https://img.shields.io/github/languages/code-size/GinOwO/GameEng) [![Build Linux](https://github.com/GinOwO/GameEng/actions/workflows/cmake-multi-platform.yml/badge.svg?event=push)](https://github.com/GinOwO/GameEng/actions/workflows/cmake-multi-platform.yml)

## Building from source
0. Dependencies
- CMake
- pkg-config
- Mesa OpenGL development files
- Wayland development files
- Wayland protocols
- Google Test development files
- XKB common library development files
- XRandR development files
- Xinerama development files
- XCursor development files
- XInput development files

On Ubuntu, you can install the following packages:
```bash
sudo apt-get install \
	cmake pkg-config \
	libgl1-mesa-dev \
	libwayland-dev wayland-protocols \
	libgtest-dev libxkbcommon-dev \
	libxrandr-dev libxinerama-dev \
	libxcursor-dev libxi-dev
```

On Fedora, you can install the following packages:
```bash
sudo dnf install \
	cmake pkgconfig \
	mesa-libGL-devel \
	wayland-devel wayland-protocols \
	gtest-devel xkbcommon-devel \
	libXrandr-devel libXinerama-devel \
	libXcursor-devel libXi-devel
```

On Arch-based systems, you can install the following packages:
```bash
yay -S \
	cmake pkg-config \
	mesa libwayland libwayland-protocols \
	gtest xkbcommon libxrandr \
	libxinerama libxcursor libxi
```

1. Clone the repository
```bash
git clone https://github.com/GinOwO/GameEng.git
cd GameEng
```

2. Create a build directory and configure CMake
```bash
mkdir -p build
cmake -B build -S .
cmake --build /home/gin/Desktop/GameEngine/build --config Debug --target all --
```

3. Built files can be found in the `build` directory
```bash
cd build
./GameEngine
```

## Tests
Git pre-push hooks can be started by running the following command:
```bash
./.githooks/init-hooks.sh
```

To run the tests, you can use the following command:
```bash
cd build/tests
ctest --rerun-failed --output-on-failure --verbose
```

## License
This project is licensed under the GPL-2.0 License - see the [LICENSE](LICENSE) file for details
