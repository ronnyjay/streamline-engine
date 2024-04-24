#pragma once

#include "engine/EBO/EBO.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <engine/VAO/VAO.hpp>
#include <engine/VBO/VBO.hpp>

#include <engine/shader/shader.hpp>
#include <engine/shader_program/shader_program.hpp>
#include <engine/window/window.hpp>

#include <imgui.h>

#include <list>
#include <string>

extern engine::window application;

namespace engine
{

namespace mesh
{

class mesh_t
{
  public:
    mesh_t(const std::basic_string<char> &name) : m_pos(0.0f), m_model(1.0f), m_name(name)
    {
        application.debug_window().add_node("Meshes");
        application.debug_window().add_child_node("Meshes", name);
        application.debug_window().add_child_node(name, name + " Children");
        application.debug_window().add_slider(name, "Position Z", &m_pos.z, []() {});
        application.debug_window().add_slider(name, "Position Y", &m_pos.y, []() {});
        application.debug_window().add_slider(name, "Position X", &m_pos.x, []() {});
    }

    virtual void update(double dt)
    {
        for (auto obj : m_meshes)
        {
            obj->update(dt);
        }
    }

    virtual void draw(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection)
    {
        for (auto obj : m_meshes)
        {
            obj->draw(m_model * model, view, projection);
        }
    }

    void set_position(float x, float y, float z)
    {
        m_pos.x = x;
        m_pos.y = y;
        m_pos.z = z;
    }

    glm::mat4 &get_model()
    {
        return m_model;
    }

    std::string get_name() const
    {
        return m_name;
    }

    void add_mesh(engine::mesh::mesh_t *const m)
    {
        application.debug_window().pop_node(m->m_name);
        application.debug_window().add_child_node(m_name + " Children", m->m_name);
        application.debug_window().add_slider(m->m_name, "Position Z", &m->m_pos.z, []() {});
        application.debug_window().add_slider(m->m_name, "Position Y", &m->m_pos.y, []() {});
        application.debug_window().add_slider(m->m_name, "Position X", &m->m_pos.x, []() {});

        m_meshes.push_back(m);
    }

  protected:
    glm::vec3 m_pos;
    glm::mat4 m_model;

    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;

    shader_program m_shader_program;

    std::string m_name;

    std::list<engine::mesh::mesh_t *> m_meshes;
};

}; // namespace mesh

}; // namespace engine