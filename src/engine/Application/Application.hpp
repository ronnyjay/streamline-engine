#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/Monitor/monitor.hpp>
#include <engine/Resolution/resolution.hpp>
#include <engine/Window/window.hpp>

#include <engine/Camera/Camera.hpp>
#include <engine/Config/Config.hpp>
#include <engine/Framebuffer/Framebuffer.hpp>
#include <engine/Scene/Scene.hpp>
#include <engine/Shader/Shader.hpp>
#include <engine/Texture/Texture.hpp>

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace engine
{

typedef std::map<int, std::shared_ptr<Camera>> CameraMap;
typedef std::map<int, std::shared_ptr<Scene>> SceneMap;
typedef std::unordered_map<int, Direction> KeyMap;
typedef std::unordered_map<std::string, ShaderProgram> ShaderMap;
typedef std::unordered_map<std::string, Texture> TextureMap;

typedef std::vector<Monitor *> MonitorList;

typedef enum
{
    FPS_30 = 30,
    FPS_60 = 60,
    FPS_120 = 120,
    FPS_144 = 144,
    FPS_165 = 165,
    FPS_240 = 240,
    FPS_360 = 360,
    FPS_UNLIMITED
} Framerate;

struct ApplicationFlags
{
    bool FirstMouse = true;
    bool CaptureMouse = true;
    bool VerticalSync = false;
    bool ShowCursor = false;
    bool ShowWireframes = false;
    bool ShowCollisions = false;
    bool ShowMetrics = false;
    bool ShowDebugWindow = false;
};

class Application
{
  public:
    Application(const int width = 800, const int height = 600, const char *title = "Untitled Application");

    int Width() const;
    int Height() const;

    ApplicationFlags &Flags();

    void AddCamera(const int, const std::shared_ptr<Camera>);
    void SetCamera(const int);
    Camera *const GetCurrentCamera() const;

    void AddScene(const int, const std::shared_ptr<Scene>);
    void SetScene(const int);
    Scene *const GetCurrentScene() const;

    ShaderProgram &GetShader(const char *);

    void BindMovementKey(const int, const Direction);

    void ShowWireframes(const bool);
    void ShowCollisions(const bool);

    void Run();

    ~Application();

  private:
    friend class Window;
    Window *m_Window;

    int m_Width;
    int m_Height;

    int m_LastWidth;
    int m_LastHeight;

    int m_WindowX;
    int m_WindowY;

    int m_MonitorIndex;

    Monitor *m_PrimaryMonitor;
    Monitor *m_CurrentMonitor;

    MonitorList m_Monitors;

    int m_FramerateIndex;
    Framerate m_Framerate;

    DisplayMode m_DisplayMode;
    DisplayMode m_LastDisplayMode;

    int m_CurrentCameraIndex;
    Camera *m_CurrentCamera;
    CameraMap m_Cameras;

    int m_CurrentSceneIndex;
    Scene *m_CurrentScene;
    SceneMap m_Scenes;

    KeyMap m_MovementBinds;

    ShaderMap m_Shaders;
    TextureMap m_Textures;

    Framebuffer *m_Framebuffer;

    Config m_VideoConfig;

    ApplicationFlags m_Flags;

    GLFWwindow *const GetWindow() const;

    Monitor *const GetPrimaryMonitor() const;
    Monitor *const GetCurrentMonitor() const;

    void ProcessInput(const double);

    void SetCameraNext();
    void SetCameraPrev();

    void SetSceneNext();
    void SetScenePrev();

    void SetResolution(const Resolution);
    void SetDisplayMode(const DisplayMode);
    void SetMonitor(Monitor *);

    void LoadMonitors();

    static const char *DisplayModes[];
    static const char *Framerates[];

    static void framebuffer_size_callback(GLFWwindow *, int, int);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void GLAPIENTRY MessageCallback(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *);
};

} // namespace engine