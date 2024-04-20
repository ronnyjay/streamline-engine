add_subdirectory(perspective)
add_subdirectory(orthographic)

add_library(camera INTERFACE)
target_link_libraries(camera INTERFACE perspective orthographic)