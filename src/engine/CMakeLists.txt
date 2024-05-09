add_library(engine STATIC)

target_sources(engine PRIVATE
    application/application.cpp
    camera/camera.cpp
    camera/orthographic/orthographic.cpp
    camera/perspective/perspective.cpp
    mesh/mesh.cpp
    mesh/pyramid/pyramid.cpp
    mesh/object/object.cpp
    mesh/object/material/material.cpp
    renderer/VAO/VAO.cpp
    renderer/VBO/VBO.cpp
    renderer/EBO/EBO.cpp
    shader/shader.cpp
    stb/stb_image.cpp
    texture/texture.cpp
    window/window.cpp
    world/world.cpp
)

target_link_libraries(engine PUBLIC glfw glm::glm glad imgui)