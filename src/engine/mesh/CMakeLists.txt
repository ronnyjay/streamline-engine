add_subdirectory(rectangle)
add_subdirectory(circle)
add_subdirectory(pyramid)
add_subdirectory(obj)

add_library(mesh INTERFACE)
target_link_libraries(mesh INTERFACE rectangle circle pyramid obj)
