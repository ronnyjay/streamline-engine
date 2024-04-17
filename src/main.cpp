
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/mesh/circle/circle.hpp>
#include <engine/mesh/pyramid/pyramid.hpp>
#include <engine/mesh/rectangle/rectangle.hpp>

#include <engine/stb/stb_image.hpp>
#include <engine/world/world.hpp>

#include <logger/logger.hpp>

int window_width = 1920;
int window_height = 1080;

const char *window_title = "streamline-engine";

void window_resize_callback(GLFWwindow *, int, int);
void window_minimized_callback(GLFWwindow *, int);
void window_maximized_callback(GLFWwindow *, int);
void window_key_callback(GLFWwindow *, int, int, int, int);

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
    glfwSetKeyCallback(window, window_key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        logger::err("Failed to initialize GLAD");
        goto endwin;
    }

    glfwSwapInterval(1);
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    {
        engine::world world;
        engine::mesh::pyramid pyramid_mesh;

        world.add_mesh(&pyramid_mesh);

        double current_time;
        double last_time;
        double dt;

        last_time = current_time = glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            dt = (current_time = glfwGetTime()) - last_time;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void window_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
}
