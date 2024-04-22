#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/config/config.hpp>
#include <engine/window/window.hpp>

#include <engine/world/world.hpp>

#include <engine/camera/orthographic/orthographic.hpp>
#include <engine/camera/perspective/perspective.hpp>

#include <engine/mesh/circle/circle.hpp>
#include <engine/mesh/pyramid/pyramid.hpp>
#include <engine/mesh/rectangle/rectangle.hpp>

#include <engine/stb/stb_image.hpp>

#include <logger/logger.hpp>

#include <irrklang/irrKlang.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void window_resize_callback(GLFWwindow *, int, int);
void window_minimized_callback(GLFWwindow *, int);
void window_maximized_callback(GLFWwindow *, int);
void window_mouse_callback(GLFWwindow *, double, double);
void window_scroll_callback(GLFWwindow *, double, double);
void window_key_callback(GLFWwindow *, int, int, int, int);
void process_input(GLFWwindow *);

bool imGui_toggle = false;

engine::window application(1920, 1080, "streamline-engine");

int main(int argc, const char *argv[])
{
    application.initialize();

    engine::camera::perspective_camera perspective_camera;
    engine::camera::orthographic_camera orthographic_camera;

    orthographic_camera.set_yaw(-45.0f);
    orthographic_camera.set_pitch(36.0f);
    orthographic_camera.invert_controls(true);

    application.add_camera(0, &perspective_camera);
    application.add_camera(1, &orthographic_camera);
    application.set_camera(1);

    engine::world world;

    engine::mesh::pyramid p0("Pyramid 0");
    engine::mesh::pyramid p1("Pyramid 1");
    engine::mesh::pyramid p2("Pyramid 2");

    p0.set_position(0.0f, 5.0f, 10.0f);
    p1.set_position(0.0f, -5.0, -10.0f);
    p2.set_position(0.0f, 0.0f, 0.0f);

    world.add_mesh(&p0);
    world.add_mesh(&p1);
    world.add_mesh(&p2);

    glfwSwapInterval(1);
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    double current_time;
    double last_time;
    double dt;

    last_time = current_time = glfwGetTime();

    while (application.running())
    {
        dt = (current_time = glfwGetTime()) - last_time;

        application.process_input();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world.update(dt);
        world.draw();

        glfwSwapBuffers(application.as_glfw_window());
        glfwPollEvents();

        last_time = current_time;
    }

    return 0;
}

// int main(int argc, const char *argv[])
// {
//     engine::config application_configuration(".streamlinerc");

//     GLFWwindow *window;

//     if (!glfwInit())
//     {
//         logger::err("Failed to initialize GLFW");
//         goto exit;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
//     if (window == NULL)
//     {
//         logger::err("Failed to create GLFW window");
//         goto cleanup;
//     }

//     glfwSetWindowAspectRatio(window, 16, 9);
//     glfwSetWindowSizeCallback(window, window_resize_callback);
//     glfwSetWindowIconifyCallback(window, window_minimized_callback);
//     glfwSetWindowMaximizeCallback(window, window_maximized_callback);
//     // glfwSetCursorPosCallback(window, window_mouse_callback);
//     glfwSetScrollCallback(window, window_scroll_callback);
//     glfwSetKeyCallback(window, window_key_callback);

//     // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//     glfwMakeContextCurrent(window);

//     if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
//     {
//         logger::err("Failed to initialize GLAD");
//         goto endwin;
//     }

//     _application.add_camera(0, &perspective_camera);
//     _application.add_camera(1, &orthographic_camera);

//     glfwSwapInterval(1);
//     stbi_set_flip_vertically_on_load(true);

//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LESS);
//     glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

//     {
//         // Setup Dear ImGui context
//         IMGUI_CHECKVERSION();
//         ImGui::CreateContext();
//         ImGuiIO &io = ImGui::GetIO();
//         io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
//         io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
//         io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

//         // Setup Platform/Renderer backends
//         ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW
//         // callbacks and chain to existing ones.

//         ImGui_ImplOpenGL3_Init();

//         engine::shader_program sp;
//         engine::shader vertex_shader("resources/shaders/text/text.vs", GL_VERTEX_SHADER);
//         engine::shader fragment_shader("resources/shaders/text/text.fs", GL_FRAGMENT_SHADER);

//         sp.add_shader(vertex_shader.id());
//         sp.add_shader(fragment_shader.id());

//         sp.link();

//         engine::world world;
//         global_camera->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
//         // global_camera.set_pitch(36.0f);

//         engine::mesh::pyramid pyramid_mesh("Pyramid 0");
//         engine::mesh::pyramid pyramid_mesh_copy("Pyramid 1");
//         engine::mesh::pyramid pyramid_mesh_copy_2("Pyramid 2");
//         engine::mesh::pyramid pyramid_mesh_copy_3("Pyramid 3");

//         pyramid_mesh_copy.set_position(10.0f, 0.0f, 15.0f);
//         pyramid_mesh_copy_2.set_position(-10.0f, 0.0f, 9.0f);
//         pyramid_mesh_copy_3.set_position(0.0f, 15.0f, 25.0f);

//         world.add_mesh(&pyramid_mesh);
//         pyramid_mesh.add_mesh(&pyramid_mesh_copy);
//         pyramid_mesh.add_mesh(&pyramid_mesh_copy_2);
//         pyramid_mesh_copy_2.add_mesh(&pyramid_mesh_copy_3);

//         world.show_wireframes(false);

//         double current_time;
//         double last_time;
//         double dt;

//         last_time = current_time = glfwGetTime();
//         double last_char = current_time;

//         std::string health(
//             "this is text. $1,000 to see how longer text works... (and parenthisis & ampersand and asterisk *)");

//         // std::string health(text);
//         auto it = health.begin();
//         std::string health_out;

//         glm::vec3 c1(100.0f / 256.0f, 120.0f / 256.0f, 170.0f / 256.0f);
//         glm::vec3 c2(100.0f / 256.0f, 200.0f / 256.0f, 0.0f);

//         glm::vec3 *cc = &c1;

//         int col = 1;

//         // SoundEngine->play2D("resources/audio/breakout.mp3", true);

//         bool show_metrics = false;
//         bool wireframes_toggle = false;

//         while (!glfwWindowShouldClose(window))
//         {
//             ImGui_ImplOpenGL3_NewFrame();
//             ImGui_ImplGlfw_NewFrame();
//             ImGui::NewFrame();

//             if (imGui_toggle)
//             {
//                 ImGui::Begin("Streamline Engine");

//                 if (ImGui::Button("Show Metrics"))
//                 {
//                     show_metrics = !show_metrics;
//                 }

//                 if (ImGui::TreeNode("Debug"))
//                 {
//                     ImGui::Text("Camera: ");
//                     ImGui::SameLine();
//                     if (ImGui::Button((_application.camera()->m_title).c_str()))
//                     {
//                         _application.toggle_camera();
//                     }

//                     ImGui::Text("Show Wireframes: ");
//                     ImGui::SameLine();
//                     if (ImGui::Button(wireframes_toggle ? "True" : "False"))
//                     {
//                         // wireframes_toggle = !wireframes_toggle;
//                         // world.show_wireframes(wireframes_toggle);
//                     }

//                     ImGui::TreePop();
//                 }

//                 if (show_metrics)
//                     ImGui::ShowMetricsWindow();

//                 ImGui::End();
//             }

//             if (current_time - last_char > 0.05)
//             {
//                 health_out.push_back(*it);
//                 it++;
//                 if (it == health.end())
//                 {
//                     it = health.begin();
//                     health_out.clear();

//                     if (col == 1)
//                     {
//                         cc = &c2;
//                         col = 2;
//                     }
//                     else
//                     {
//                         cc = &c1;
//                         col = 1;
//                     }
//                 }

//                 last_char = current_time;
//             }

//             glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//             engine::text health_text(health_out, -0.95, +0.88, 0.45f, *cc, 0.9f);

//             dt = (current_time = glfwGetTime()) - last_time;

//             process_input(window);

//             world.update(dt);
//             world.draw();

//             health_text.draw(sp);

//             last_time = current_time;

//             ImGui::Render();
//             ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//             glfwSwapBuffers(window);
//             glfwPollEvents();
//         }
//     }

//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

// endwin:
//     glfwDestroyWindow(window);

// cleanup:
//     glfwTerminate();

// exit:
//     return 0;
// }

// void window_resize_callback(GLFWwindow *window, int width, int height)
// {
//     window_width = width;
//     window_height = height;

//     glViewport(0, 0, width, height);
// }

// void window_minimized_callback(GLFWwindow *window, int minimized)
// {
//     minimized ? glfwIconifyWindow(window) : glfwRestoreWindow(window);
// }

// void window_maximized_callback(GLFWwindow *window, int maximized)
// {
//     maximized ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
// }

// void window_mouse_callback(GLFWwindow *window, double xpos_in, double ypos_in)
// {
//     float xpos = static_cast<float>(xpos_in);
//     float ypos = static_cast<float>(ypos_in);

//     if (first_mouse)
//     {
//         last_x = xpos;
//         last_y = ypos;
//         first_mouse = false;
//     }

//     float xoffset = xpos - last_x;
//     float yoffset = last_y - ypos;

//     last_x = xpos;
//     last_y = ypos;

//     _application.camera()->move(xoffset, yoffset);
// }

// void window_scroll_callback(GLFWwindow *, double xoffset, double yoffset)
// {
//     _application.camera()->move(static_cast<float>(yoffset));
// }

// void window_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
// {
//     if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
//     {
//         imGui_toggle = !imGui_toggle;
//     }
// }

// void process_input(GLFWwindow *window)
// {
//     // movement
//     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//     {
//         _application.camera()->move(engine::camera::UP);
//     }
//     if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//     {
//         _application.camera()->move(engine::camera::DOWN);
//     }
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//     {
//         _application.camera()->move(engine::camera::FORWARD);
//     }
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//     {
//         _application.camera()->move(engine::camera::BACKWARD);
//     }
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//     {
//         _application.camera()->move(engine::camera::RIGHT);
//     }
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//     {
//         _application.camera()->move(engine::camera::LEFT);
//     }

//     // exit
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     {
//         glfwSetWindowShouldClose(window, GL_TRUE);
//     }
// }
