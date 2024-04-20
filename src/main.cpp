#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/world/world.hpp>

#include <engine/camera/orthographic/orthographic.hpp>
#include <engine/camera/perspective/perspective.hpp>

#include <engine/mesh/circle/circle.hpp>
#include <engine/mesh/pyramid/pyramid.hpp>
#include <engine/mesh/rectangle/rectangle.hpp>

#include <engine/stb/stb_image.hpp>

#include <logger/logger.hpp>

void window_resize_callback(GLFWwindow *, int, int);
void window_minimized_callback(GLFWwindow *, int);
void window_maximized_callback(GLFWwindow *, int);
void window_mouse_callback(GLFWwindow *, double, double);
void window_scroll_callback(GLFWwindow *, double, double);
void process_input(GLFWwindow *);

int window_width = 1920;
int window_height = 1080;

const char *window_title = "streamline-engine";

engine::camera::perspective_camera global_camera;

float last_x = window_width / 2.0f;
float last_y = window_height / 2.0f;
bool first_mouse = true;

int main(int argc, const char *argv[])
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        logger::err("Failed to initialize GLFW");
        goto exit;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    if (window == NULL)
    {
        logger::err("Failed to create GLFW window");
        goto cleanup;
    }

    glfwSetWindowAspectRatio(window, 16, 9);
    glfwSetWindowSizeCallback(window, window_resize_callback);
    glfwSetWindowIconifyCallback(window, window_minimized_callback);
    glfwSetWindowMaximizeCallback(window, window_maximized_callback);
    glfwSetCursorPosCallback(window, window_mouse_callback);
    glfwSetScrollCallback(window, window_scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        logger::err("Failed to initialize GLAD");
        goto endwin;
    }

    glfwSwapInterval(1);
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    {
        engine::world world;
        global_camera.set_position(glm::vec3(0.0f, 0.0f, 0.0f));
        global_camera.set_rotation(engine::camera::rotation_axis::x, 90.0f);

        engine::mesh::pyramid pyramid_mesh;
        engine::mesh::pyramid pyramid_mesh_copy;
        engine::mesh::pyramid pyramid_mesh_copy_2;
        engine::mesh::pyramid pyramid_mesh_copy_3;

        pyramid_mesh_copy.set_position(10.0f, 0.0f, 15.0f);
        pyramid_mesh_copy_2.set_position(-10.0f, 0.0f, 9.0f);
        pyramid_mesh_copy_3.set_position(0.0f, 15.0f, 25.0f);

        world.add_mesh(&pyramid_mesh);
        world.add_mesh(&pyramid_mesh_copy);
        world.add_mesh(&pyramid_mesh_copy_2);
        world.add_mesh(&pyramid_mesh_copy_3);

        world.show_wireframes(false);

        double current_time;
        double last_time;
        double dt;

        last_time = current_time = glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            dt = (current_time = glfwGetTime()) - last_time;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            process_input(window);

            world.update(dt);
            world.draw();

            glfwSwapBuffers(window);
            glfwPollEvents();

            last_time = current_time;
        }
    }

endwin:
    glfwDestroyWindow(window);

cleanup:
    glfwTerminate();

exit:
    return 0;
}

void window_resize_callback(GLFWwindow *window, int width, int height)
{
    window_width = width;
    window_height = height;

    glViewport(0, 0, width, height);
}

void window_minimized_callback(GLFWwindow *window, int minimized)
{
    minimized ? glfwIconifyWindow(window) : glfwRestoreWindow(window);
}

void window_maximized_callback(GLFWwindow *window, int maximized)
{
    maximized ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
}

void window_mouse_callback(GLFWwindow *window, double xpos_in, double ypos_in)
{
    float xpos = static_cast<float>(xpos_in);
    float ypos = static_cast<float>(ypos_in);

    if (first_mouse)
    {
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos;

    last_x = xpos;
    last_y = ypos;

    global_camera.move(xoffset, yoffset);
}

void window_scroll_callback(GLFWwindow *, double xoffset, double yoffset)
{
    global_camera.move(static_cast<float>(yoffset));
}

void process_input(GLFWwindow *window)
{
    // movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        global_camera.move(engine::camera::forward);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        global_camera.move(engine::camera::backward);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        global_camera.move(engine::camera::left);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        global_camera.move(engine::camera::right);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        global_camera.move(engine::camera::up);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        global_camera.move(engine::camera::down);
    }

    // exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
