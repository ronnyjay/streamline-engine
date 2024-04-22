#include <engine/window/window.hpp>
#include <stdexcept>

using namespace engine;

window::window()
    : m_window_width(800), m_window_height(600), m_window_title("Untitled Application"), m_cursor_x(0), m_cursor_y(0),
      m_sound_engine(irrklang::createIrrKlangDevice())
{
}

window::window(int width, int height, const char *title)
    : m_window_width(width), m_window_height(height), m_window_title(title), m_cursor_x(0), m_cursor_y(0),
      m_sound_engine(irrklang::createIrrKlangDevice())
{
}

void window::configure(config configuration)
{
    configuration.load();

    if (configuration.has("window-width") && configuration.has("window-height"))
    {
        m_window_width = std::stoi(configuration.get("window-width"));
        m_window_width = std::stoi(configuration.get("window-height"));
    }

    if (configuration.has("window-title"))
    {
        m_window_title = configuration.get("window-title").c_str();
    }

    if (configuration.has("aspect-ratio"))
    {
    }
}

void window::initialize()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_title, NULL, NULL);
    if (m_window == NULL)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowAspectRatio(m_window, m_window_width, m_window_height);
    glfwSetWindowSizeCallback(m_window, window::resize_callback);
    glfwSetWindowIconifyCallback(m_window, window::minimized_callback);
    glfwSetWindowMaximizeCallback(m_window, window::maximized_callback);
    glfwSetKeyCallback(m_window, window::key_callback);
    glfwSetCursorPosCallback(m_window, window::cursor_callback);
    glfwSetScrollCallback(m_window, window::scroll_callback);
    glfwSetWindowUserPointer(m_window, this); // use member functions in callbacks
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    m_debugger.add_node("Debug");

    m_debugger.add_option("Debug", "Show Wireframes", false,
                          [](bool wireframes)
                          {
                              if (wireframes)
                                  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                              else
                                  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                          });

    m_debugger.initialize(m_window);
}

void window::add_camera(int key, camera::camera_t *camera)
{
    if (key < 0)
    {
        throw std::runtime_error("Key must be a value greater than or equal to 0.");
    }

    m_cameras.emplace(key, camera);

    if (m_camera == nullptr)
    {
        m_camera = camera;
    }
}

void window::set_camera(int key)
{
    auto entry = m_cameras.find(key);

    if (entry == m_cameras.end())
    {
        throw std::runtime_error("Camera does not exist.");
    }

    m_camera = entry->second;
}

void window::toggle_camera()
{
    if (m_cameras.size() < 2)
    {
        return;
    }

    for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it)
    {

        if (it->second == m_camera)
        {
            auto next = it;

            if (++next == m_cameras.end())
            {
                m_camera = m_cameras.begin()->second;
            }
            else
            {
                m_camera = next->second;
            }

            break;
        }
    }
}

void window::process_input()
{
    // movement
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        m_camera->move(engine::camera::UP);
    }
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_camera->move(engine::camera::DOWN);
    }
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_camera->move(engine::camera::FORWARD);
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_camera->move(engine::camera::BACKWARD);
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_camera->move(engine::camera::RIGHT);
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_camera->move(engine::camera::LEFT);
    }

    // exit
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }
}

void window::resize_callback(GLFWwindow *window, int width, int height)
{
    auto instance = static_cast<class window *>(glfwGetWindowUserPointer(window));

    instance->m_window_width = width;
    instance->m_window_height = height;

    glViewport(0, 0, width, height);
}

void window::minimized_callback(GLFWwindow *window, int minimized)
{
    minimized ? glfwIconifyWindow(window) : glfwRestoreWindow(window);

    auto instance = static_cast<class window *>(glfwGetWindowUserPointer(window));
    glfwGetWindowSize(instance->m_window, &instance->m_window_width, &instance->m_window_height);
}

void window::maximized_callback(GLFWwindow *window, int maximized)
{
    maximized ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);

    auto instance = static_cast<class window *>(glfwGetWindowUserPointer(window));
    glfwGetWindowSize(instance->m_window, &instance->m_window_width, &instance->m_window_height);
}

void window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
}

void window::cursor_callback(GLFWwindow *window, double xpos_in, double ypos_in)
{
    auto instance = static_cast<class window *>(glfwGetWindowUserPointer(window));

    float xpos = static_cast<float>(xpos_in);
    float ypos = static_cast<float>(ypos_in);

    float xoffset = xpos - instance->m_cursor_x;
    float yoffset = instance->m_cursor_y - ypos;

    instance->m_cursor_x = xpos;
    instance->m_cursor_y = ypos;

    instance->camera()->move(xoffset, yoffset);
}

void window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    auto instance = static_cast<class window *>(glfwGetWindowUserPointer(window));
    instance->camera()->move(static_cast<float>(yoffset));
}