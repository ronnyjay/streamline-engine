add_subdirectory(engine)
add_subdirectory(glad)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} engine glad)
