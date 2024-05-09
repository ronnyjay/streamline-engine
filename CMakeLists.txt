cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "streamline-engine")
project(${PROJECT_NAME})

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

set(GLM_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/glm/1.0.1/include")

if(IS_DIRECTORY ${GLM_OSX_INCLUDE_DIR})
  include_directories(${GLM_OSX_INCLUDE_DIR})
  include_directories(/opt/homebrew/Cellar/glfw/3.3.2/include)  # Adjust the version/path as necessary
endif()

add_compile_options(
    -Werror
    -Wall
    -Wpedantic
    -g
)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

include_directories(
    src
    extern/imgui
    extern/imgui/backends
)

add_library(imgui STATIC
    extern/imgui/imgui.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_demo.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
)

target_link_libraries(imgui PRIVATE glfw)

add_subdirectory(src)