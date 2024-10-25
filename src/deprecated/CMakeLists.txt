add_library(engine STATIC)

target_sources(engine PRIVATE
  application/application.cpp
  application/monitor.cpp
  application/resolution.cpp
  application/window.cpp
  application/window_config.cpp
  framebuffer/framebuffer.cpp
  shader/shader.cpp
  texture/texture.cpp
  resource_manager/resource_manager.cpp 
  user_interface/ui_element.cpp
  user_interface/user_interface.cpp
  # Camera/Camera.cpp
  # Camera/Orthographic.cpp
  # Camera/Perspective.cpp
  # Components/AABB.cpp
  # Components/BSphere.cpp
  # Components/Mesh.cpp
  # Components/Model.cpp
  # Components/Transform.cpp
  # Components/RigidBody.cpp
  # Config/Config.cpp
  # Entity/Entity.cpp
  # Framebuffer/Framebuffer.cpp
  # InputManager/InputManager.cpp
  # Logger/Logger.cpp
  # Scene/Scene.cpp
  # stb/stb_image.cpp
  # Text/Text.cpp
)

target_link_libraries(engine PUBLIC glfw glm::glm glad imgui assimp::assimp stb)
