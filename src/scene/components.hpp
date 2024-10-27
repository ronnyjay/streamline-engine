#pragma once

#include "core/resource_manager.hpp"

#include "renderer/model.hpp"
#include "renderer/shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>

namespace engine
{

struct ModelComponent
{

    ModelComponent(Model &model)
        : model(model)
    {
        m_shader = ResourceManager::GetShader("model");
    }

    /**
     * @brief
     *
     */
    void draw()
    {
        model.draw(m_shader);
    }

    void draw(const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model)
    {
        m_shader.use();

        m_shader.set_mat4("projection", proj);
        m_shader.set_mat4("view", view);
        m_shader.set_mat4("model", model);

        this->model.draw(m_shader);
    }

    void attach_shader(Shader &shader)
    {
        m_shader = shader;
    }

    Model &model;

  private:
    Shader m_shader;
};

} // namespace engine