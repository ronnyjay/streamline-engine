#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/camera/camera.hpp>
#include <engine/framebuffer/framebuffer.hpp>
#include <engine/scene/scene.hpp>
#include <engine/shader/shader.hpp>

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace engine
{

typedef std::map<int, std::shared_ptr<Camera>> CameraMap;
typedef std::map<int, std::shared_ptr<Scene>> SceneMap;
typedef std::unordered_map<int, Direction> KeyMap;
typedef std::unordered_map<std::string, Shader> ShaderMap;

struct Resolution
{
    Resolution(const int width, const int height, const int rate) : Width(width), Height(height), RefreshRate(rate)
    {
    }

    bool operator==(const Resolution &other) const
    {
        return Width == other.Width && Height == other.Height;
    }

    bool operator<(const Resolution &other) const
    {
        if (Width != other.Width)
        {
            return Width < other.Width;
        }

        return Height < other.Height;
    }

    int Width;
    int Height;
    int RefreshRate;

    mutable char TextFormat[32];

    const char *Format() const
    {
        std::snprintf(TextFormat, sizeof(TextFormat), "%dx%d (%d)", Width, Height, RefreshRate);
        return TextFormat;
    }
};

typedef std::vector<Resolution> ResolutionList;

struct ApplicationFlags
{
    bool FirstMouse = true;
    bool CaptureMouse = true;
    bool ShowCursor = true;
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

    void AddCamera(int, std::shared_ptr<Camera>);
    void SetCamera(int);
    Camera *const GetCurrentCamera() const;

    void AddScene(int, std::shared_ptr<Scene>);
    void SetScene(int);
    Scene *const GetCurrentScene() const;

    void LoadShader(const std::string &, const std::string &, const std::string &);
    Shader &GetShader(const std::string &);

    void BindMovementKey(int, const Direction);

    void ShowWireframes(const bool);
    void ShowCollisions(const bool);

    void Run();

    ~Application();

  private:
    GLFWwindow *m_Window;
    GLFWmonitor *m_Monitor;

    int m_Width;
    int m_Height;

    int m_CurrentCameraIndex;
    Camera *m_CurrentCamera;
    CameraMap m_CameraMap;

    int m_CurrentSceneIndex;
    Scene *m_CurrentScene;
    SceneMap m_SceneMap;

    ShaderMap m_ShaderMap;
    KeyMap m_KeyMap;

    int m_ResolutionIndex;
    ResolutionList m_ResolutionList;

    Framebuffer m_Framebuffer;

    ApplicationFlags m_Flags;

    GLFWwindow *const GetWindow() const;
    GLFWmonitor *const GetMonitor() const;

    bool IsFullscreen();
    void LoadResolutions();

    void ProcessInput();

    void SetCameraNext();
    void SetCameraPrev();

    void SetSceneNext();
    void SetScenePrev();

    void ToggleWireframes();

    static void FramebufferSizeCallback(GLFWwindow *, int, int);
    static void MinimizeCallback(GLFWwindow *, int);
    static void MaximizeCallback(GLFWwindow *, int);
    static void KeyCallback(GLFWwindow *, int, int, int, int);
    static void CursorPosCallback(GLFWwindow *, double, double);
    static void ScrollCallback(GLFWwindow *, double, double);
};

}; // namespace engine