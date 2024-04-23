#include <engine/camera/orthographic/orthographic.hpp>
#include <engine/camera/perspective/perspective.hpp>
#include <engine/mesh/pyramid/pyramid.hpp>
#include <engine/text/text.hpp>
#include <engine/window/window.hpp>
#include <engine/world/world.hpp>

#include <logger/logger.hpp>

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
    application.set_camera(0);

    engine::world world;

    engine::mesh::pyramid p0("Pyramid 0");
    engine::mesh::pyramid p1("Pyramid 1");
    engine::mesh::pyramid p2("Pyramid 2");
    engine::mesh::pyramid p4("Master Pyramid");

    p0.set_position(0.0f, 5.0f, 10.0f);
    p1.set_position(0.0f, -5.0, -10.0f);
    p2.set_position(0.0f, 0.0f, 0.0f);
    p4.set_position(0.0f, 0.0f, 5.0f);

    p4.add_mesh(&p0);
    p4.add_mesh(&p1);
    p4.add_mesh(&p2);

    world.add_mesh(&p4);

    engine::shader_program sp;
    engine::shader vertex_shader("resources/shaders/text/text.vs", GL_VERTEX_SHADER);
    engine::shader fragment_shader("resources/shaders/text/text.fs", GL_FRAGMENT_SHADER);

    sp.add_shader(vertex_shader.id());
    sp.add_shader(fragment_shader.id());
    sp.link();

    std::string health("Streamline Engine ");

    auto it = health.begin();
    std::string health_out;

    glm::vec3 color(1.0f, 1.0f, 1.0f);

    glfwSwapInterval(1);
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);

    double current_time;
    double last_time;
    double dt;

    last_time = current_time = glfwGetTime();
    double last_char = current_time;

    while (application.running())
    {
        dt = (current_time = glfwGetTime()) - last_time;

        application.process_input();

        if (current_time - last_char > 0.15)
        {
            health_out.push_back(*it);
            it++;
            if (it == health.end())
            {
                it = health.begin();
                health_out.clear();
            }

            last_char = current_time;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        engine::text health_text(health_out, -0.95, +0.88, 0.45f, color, 0.9f);

        world.update(dt);
        world.draw();

        application.debug_window().render();
        health_text.draw(sp);

        glfwSwapBuffers(application.as_glfw_window());
        glfwPollEvents();

        last_time = current_time;
    }

    return 0;
}
