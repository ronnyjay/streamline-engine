add_subdirectory(engine)
add_subdirectory(logger)
add_subdirectory(glad)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(irrklang)

target_link_libraries(${PROJECT_NAME} engine logger glfw glm::glm glad IrrKlang imgui)
