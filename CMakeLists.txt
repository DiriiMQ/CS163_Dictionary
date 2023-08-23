cmake_minimum_required(VERSION 3.26)
project(CS163_Group9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#######################################RAYLIB#######################################
# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
#######################################RAYLIB#######################################

include_directories(${CMAKE_SOURCE_DIR}/source ${CMAKE_SOURCE_DIR}/external)

add_executable(CS163_Group9 main.cpp
        external/raygui.h
        source/Window.cpp
        source/Window.h
        source/stuff/Constants.h
        source/draw/MainMenu.cpp
        source/draw/MainMenu.h
        source/core/Api.cpp
        source/core/Api.h
        source/core/Dict.cpp
        source/core/Dict.h
        source/core/Word.cpp
        source/core/Word.h
        source/core/Quiz.cpp
        source/core/Quiz.h
        source/stuff/Utils.h
        source/core/Trie.cpp
        source/core/Trie.h
        source/core/Map.hpp
        source/core/CompareString.h
        source/_raygui.h
        source/stuff/Button.cpp
        source/stuff/Button.h
        source/stuff/SearchBox.cpp
        source/stuff/SearchBox.h
        source/stuff/SuggestionLine.cpp
        source/stuff/SuggestionLine.h
        source/stuff/FrameBoard.cpp
        source/stuff/FrameBoard.h
        source/draw/Favorite.cpp
        source/draw/Favorite.h
        source/draw/QuizScene.cpp
        source/draw/QuizScene.h
)
target_link_libraries(${PROJECT_NAME} raylib)
