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

engine::camera::orthographic_camera perspective_camera;

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
}

void window_scroll_callback(GLFWwindow *, double x_offset, double y_offset)
{
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        perspective_camera.move(engine::camera::forward);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        perspective_camera.move(engine::camera::backward);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        perspective_camera.move(engine::camera::left);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        perspective_camera.move(engine::camera::right);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
