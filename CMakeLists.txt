cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 23)

set(PROJECT_NAME "streamline-engine")
project(${PROJECT_NAME})

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

set(GLM_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/glm/1.0.1/include")
set(GLFW_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/glfw/3.3.2/include")
set(ASSIMP_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/assimp/5.4.1/include")

if(APPLE AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(IS_DIRECTORY ${GLM_OSX_INCLUDE_DIR})
        include_directories(${GLM_OSX_INCLUDE_DIR})
    endif()
    if(IS_DIRECTORY ${GLFW_OSX_INCLUDE_DIR})
        include_directories(${GLFW_OSX_INCLUDE_DIR})  
    endif()
    if(IS_DIRECTORY ${ASSIMP_OSX_INCLUDE_DIR})
        include_directories(${ASSIMP_OSX_INCLUDE_DIR})
    endif()
endif()

add_compile_options(
    -Werror
    -Wall
    -Wpedantic
    -Wno-unused-but-set-variable
    -Wno-unused
    -g
)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

include_directories(
    src
    extern/imgui
    extern/imgui/backends
    extern/entt/src
    extern
    ${ASSIMP_INCLUDE_DIRS}
)

add_library(stb STATIC
    extern/stb/stb_image.cpp
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
add_subdirectory(extern/entt)

add_executable(${PROJECT_NAME} src/main.cpp)
add_subdirectory(src)
