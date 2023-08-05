# CMakeList.txt : CMake project for CMake01, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMake01 "CMake01.cpp" "CMake01.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMake01 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
