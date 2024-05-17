#include <engine/mesh/mesh.hpp>

#include <glm/ext/matrix_transform.hpp>

using namespace engine;

void Mesh::update(double dt)
{
    m_rotation_angle += m_rotation_speed * dt;

    if (m_rotation_angle >= 360.0f)
    {
        m_rotation_angle = -360.0f;
    }

    m_model = glm::translate(glm::mat4(1.0f), m_position);
    m_model = glm::translate(m_model, glm::vec3(0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotation_angle), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::translate(m_model, glm::vec3(0.0f));

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
        ImGui::DragFloat("Rotation Angle", &m_rotation_angle);
        ImGui::DragFloat("Rotation Speed", &m_rotation_speed);

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

const float Mesh::rotation_angle() const
{
    return m_rotation_angle;
}

void Mesh::set_rotation_angle(const float angle)
{
    m_rotation_angle = angle;
}

const float Mesh::rotation_speed() const
{
    return m_rotation_speed;
}

void Mesh::set_rotation_speed(const float speed)
{
    m_rotation_speed = speed;
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
