#include <engine/mesh/mesh.hpp>

using namespace engine;

void Mesh::update(double dt)
{
    for (auto &child : m_children)
    {
        child->update(dt);
    }
}

void Mesh::draw(const glm::mat4 &view, const glm::mat4 &model, const glm::mat4 &projection)
{
    for (auto &child : m_children)
    {
        child->draw(view, model * m_model, projection);
    }
}

void Mesh::draw_debug_info()
{
    if (ImGui::TreeNode(identifier().c_str()))
    {
        ImGui::DragFloat("Position X", &m_position.x);
        ImGui::DragFloat("Position Y", &m_position.y);
        ImGui::DragFloat("Position Z", &m_position.z);

        if (ImGui::TreeNode((identifier() + " Children").c_str()))
        {
            for (auto &mesh : m_children)
            {
                mesh->draw_debug_info();
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
}

const glm::vec3 &Mesh::position() const
{
    return m_position;
}

void Mesh::set_position(const glm::vec3 &position)
{
    m_position = position;
}

const glm::mat4 &Mesh::model() const
{
    return m_model;
}

void Mesh::set_model(const glm::mat4 &model)
{
    m_model = model;
}

const std::list<Mesh *> &Mesh::children() const
{
    return m_children;
}

void Mesh::add_child(Mesh *const child)
{
    m_children.push_back(child);
}
