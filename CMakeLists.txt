cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 23)

project(streamline-engine)

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
    extern
    extern/entt/src
    extern/glad
    extern/stb
    extern/imgui
    extern/imgui/backends
)

add_subdirectory(extern/entt)

add_library(glad STATIC
    extern/glad/gl.c
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

add_executable(streamline-engine src/main.cpp)

target_sources(streamline-engine PRIVATE
    src/core/application.cpp
    src/core/config.cpp
    src/core/debug.cpp
    src/core/logger.cpp
    src/core/resource_manager.cpp
    src/core/window.cpp
    src/renderer/framebuffer.cpp
    src/renderer/mesh.cpp
    src/renderer/model.cpp
    src/renderer/renderer.cpp
    src/renderer/shader.cpp
    src/renderer/texture.cpp
    src/scene/components/camera.cpp
    src/scene/components/input.cpp
    src/scene/entity.cpp
    src/scene/scene.cpp
    src/util/input_manager.cpp
)

target_link_libraries(streamline-engine PUBLIC glfw glm::glm glad stb imgui assimp::assimp)
