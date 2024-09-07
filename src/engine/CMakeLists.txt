add_library(engine STATIC)

target_sources(engine PRIVATE
  core/application.cpp
  core/window.cpp
  Application/Application.cpp
  Camera/Camera.cpp
  Camera/Orthographic.cpp
  Camera/Perspective.cpp
  Components/AABB.cpp
  Components/BSphere.cpp
  Components/Mesh.cpp
  Components/Model.cpp
  Components/Transform.cpp
  Components/RigidBody.cpp
  Config/Config.cpp
  Entity/Entity.cpp
  Framebuffer/Framebuffer.cpp
  InputManager/InputManager.cpp
  Logger/Logger.cpp
  ResourceManager/ResourceManager.cpp 
  Scene/Scene.cpp
  Shader/Shader.cpp
  stb/stb_image.cpp
  Text/Text.cpp
  Texture/Texture.cpp
)

target_link_libraries(engine PUBLIC glfw glm::glm glad imgui assimp::assimp)