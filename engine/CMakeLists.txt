cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

project(engine)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(STREAMLINE_COMPILER_GCC)
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang") 
    add_compile_definitions(STREAMLINE_COMPILER_CLANG)
endif()

set(OSX_INCLUDE_DIR "/opt/homebrew/include")

if(APPLE AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(IS_DIRECTORY ${OSX_INCLUDE_DIR})
        include_directories(${OSX_INCLUDE_DIR})
    endif()
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)
find_package(glm REQUIRED)

add_compile_options(
    -Werror
    -Wall    
    -Wpedantic
    -Wno-unused
    -march=native
)

file(GLOB SUBSYSTEM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/subsystems/*.cpp")
file(GLOB RENDERER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/*.cpp")
file(GLOB SCENE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp")
file(GLOB SYSTEM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/scene/systems/*.cpp")
file(GLOB CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp")

set (ENGINE_SOURCES ${CORE_SOURCES} ${SCENE_SOURCES} ${SYSTEM_SOURCES} ${RENDERER_SOURCES} ${SUBSYSTEM_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/../vendor/glad/gl.c    
)

add_library(stb STATIC
    ${CMAKE_SOURCE_DIR}/../vendor/stb/stb_image.cpp    
)

add_library(imgui STATIC
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/../vendor/imgui/backends/imgui_impl_glfw.cpp
)

add_executable(engine src/main.cpp)

target_sources(engine PRIVATE ${ENGINE_SOURCES})

target_include_directories(engine PRIVATE
    ${CMAKE_SOURCE_DIR}/../vendor/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/backends
)

target_include_directories(imgui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/backends
)

target_link_libraries(imgui PRIVATE glfw)

target_link_libraries(engine PRIVATE glfw glm::glm glad imgui stb assimp::assimp)

add_subdirectory(test)