# CS163 Project: Dictionary

Author: 

- 22125083 - Phan Minh Quang
- 22125081 - Dương Minh Quang
- ? - Nguyễn Quốc Nghĩa
- ? - Ngô Trí Sĩ

Our project provide a customize dictionary using some algorithms and data structures to improve the user experience.

## How to run

### Requirements

(this application works only on Windows because of using `wchar_t` which has different size on different platforms)

- C++ 17 – GNU GCC 7.3.0+
    - Please follow [this instruction](https://www.msys2.org/#installation) to install.
    - **Note**: Please install the `MinGW 64-bit` version. At step 6, please run the following command instead:
      - `pacman -S mingw-w64-x86_64-gcc`
- [CMake 3.26+](https://cmake.org/download/)
- Makefile
  - Please open the `MSYS2 MinGW 64-bit` terminal and run the following command:
    - `pacman -S make`

### Build

- Clone this repository
- Run the following commands:
  - `cd Visualgo_CS162`
  - Build the project:
    - for Windows users:
      - `cmake -G"MSYS Makefiles" -S . -B build`
  - `make -C build`
- The executable file will be in the `build` folder

### Run

- Click on the executable file in the folder `build` to run the program.
- If you want to run the program in the terminal, run the following command:
  - `cd build && ./Visualgo_CS162`

## Project structure

- `assets` – contains the assets used in the program
- `build` – contains the executable file
- `include` – contains the header and source files of the program
  - `core` – contains the core classes of the program
  - `draw` - contains the classes that draw objects structures
  - `stuff` - contains other classes that are used in the program

## Features
<!-- Brief all features with those pics? is it necessary? -->

## Data structures and algorithms
<!-- Write the DSAs and Algorithms IN DETAILS and calculate the time and space complexity with the real time measurement -->

## License

This project is licensed under the `GPL-3.0 License` - see the [LICENSE](./LICENSE) file for details.