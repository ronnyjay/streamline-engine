add_library(engine STATIC)

target_sources(engine PRIVATE
    application/application.cpp
    camera/camera.cpp
    camera/orthographic.cpp
    camera/perspective.cpp
    collider/collider.cpp
    entity/entity.cpp
    framebuffer/framebuffer.cpp
    logger/logger.cpp
    mesh/mesh.cpp
    model/model.cpp
    scene/scene.cpp
    shader/shader.cpp
    stb/stb_image.cpp
    text/text.cpp
    texture/texture.cpp
)

target_link_libraries(engine PUBLIC glfw glm::glm glad imgui assimp::assimp)