#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/camera/camera.hpp>
#include <engine/config/config.hpp>
#include <engine/framebuffer/framebuffer.hpp>
#include <engine/scene/scene.hpp>
#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

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

struct Resolution
{
    Resolution(const int width, const int height)
        : m_Width(width)
        , m_Height(height)
    {
    }

    bool operator==(const Resolution &other) const
    {
        return m_Width == other.m_Width && m_Height == other.m_Height;
    }

    bool operator<(const Resolution &other) const
    {
        if (m_Width != other.m_Width)
        {
            return m_Width < other.m_Width;
        }

        return m_Height < other.m_Height;
    }

    int m_Width;
    int m_Height;

    mutable char m_TextFormat[32];

    const char *Format() const
    {
        std::snprintf(m_TextFormat, sizeof(m_TextFormat), "%dx%d", m_Width, m_Height);
        return m_TextFormat;
    }
};

typedef std::vector<Resolution> ResolutionList;

struct Monitor
{
    Monitor(GLFWmonitor *monitor)
        : m_Monitor(monitor)
        , m_Title(glfwGetMonitorName(monitor))
        , m_ResolutionWindowed(-1)
    {
        glfwGetMonitorWorkarea(monitor, &m_PositionX, &m_PositionY, &m_Width, &m_Height);
        glfwGetMonitorContentScale(monitor, &m_ScaleX, &m_ScaleY);

        int count;
        const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

        for (int i = 0; i < count; i++)
        {
            m_Resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
        }

        m_Resolutions.erase(std::unique(m_Resolutions.begin(), m_Resolutions.end()), m_Resolutions.end());

        m_ResolutionFullscreen = m_Resolutions.size() - 1;
        m_ResolutionBorderless = m_Resolutions.size() - 1;
    }

    bool operator==(const Monitor &other)
    {
        return m_Monitor == other.m_Monitor;
    }

    bool operator!=(const Monitor &other)
    {
        return m_Monitor != other.m_Monitor;
    }

    GLFWmonitor *m_Monitor;

    int m_Width;
    int m_Height;

    int m_PositionX;
    int m_PositionY;

    float m_ScaleX;
    float m_ScaleY;

    const char *m_Title;

    int m_ResolutionFullscreen;
    int m_ResolutionWindowed;
    int m_ResolutionBorderless;

    ResolutionList m_Resolutions;
};

typedef std::vector<Monitor *> MonitorList;

typedef enum
{
    Fullscreen = 0,
    Windowed = 1,
    Borderless = 2
} DisplayMode;

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

    ApplicationFlags const &Flags() const;

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
    GLFWwindow *m_Window;

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

    static void FramebufferSizeCallback(GLFWwindow *, int, int);
    static void MinimizeCallback(GLFWwindow *, int);
    static void MaximizeCallback(GLFWwindow *, int);
    static void KeyCallback(GLFWwindow *, int, int, int, int);
    static void CursorPosCallback(GLFWwindow *, double, double);
    static void ScrollCallback(GLFWwindow *, double, double);
    static void GLAPIENTRY MessageCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);
};

}; // namespace engine