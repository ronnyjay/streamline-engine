add_subdirectory(engine)
add_subdirectory(libstreamline)
add_subdirectory(glad)

target_link_libraries(${PROJECT_NAME}
    glad
    engine
    libstreamline
)
