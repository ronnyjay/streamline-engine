cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "streamline-engine")
project(${PROJECT_NAME})

find_package(glfw3 3.3 REQUIRED)
find_package(glm)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

add_compile_options(
  -Werror
  -Wall
  -Wpedantic
)

set(GLM_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/glm/1.0.1/include")

if(IS_DIRECTORY ${GLM_OSX_INCLUDE_DIR})
  include_directories(${GLM_OSX_INCLUDE_DIR})
endif()

include_directories(
  ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(src)