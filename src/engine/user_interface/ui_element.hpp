#pragma once

#include <glm/fwd.hpp>

#include <functional>

#include <engine/resource_manager/resource_manager.hpp>
#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

namespace engine
{

struct click_data
{
    int button;
    int action;
};

class ui_element
{
  public:
    ui_element(shader_program &shader)
        : m_shader(shader)
        , m_x(0)
        , m_y(0)
        , m_hovered(false)
        , m_width(0)
        , m_height(0)
        , m_on_click([](click_data c) {})
        , m_on_hover([](bool hovering) {})
    {
    }

    virtual ~ui_element()
    {
    }

    void set_projection(const glm::mat4 &proj)
    {
        m_proj = proj;

        // auto view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // m_shader.set_mat4("projection", m_proj);
        // m_shader.set_mat4("view", view);
        // m_shader.set_mat4("model", glm::mat4(1.0f));
    }

    virtual bool is_point_inside(const float x, const float y) const
    {
        glm::vec4 model_pos(m_x - (m_width / 2.0f), m_y - (m_height / 2.0f), 0.0, 1.0);
        glm::vec4 model_dimensions(m_width, m_height, 0.0, 1.0);

        glm::vec4 screen_pos = m_proj * model_pos;
        glm::vec4 screen_dimensions = m_proj * model_dimensions;

        return x < screen_pos.x + screen_dimensions.x && x > screen_pos.x && y < screen_pos.y + screen_dimensions.y &&
               y > screen_pos.y;
    }

    virtual void click(int button, int action)
    {
        m_on_click(click_data{button, action});
    }

    virtual void hover(const bool hovering)
    {
        if (hovering != m_hovered)
            m_on_hover(hovering);

        m_hovered = hovering;
    }

    void set_width(const float width)
    {
        m_width = width;
    }

    void set_height(const float height)
    {
        m_height = height;
    }

    virtual void set_pos(const float x, const float y)
    {
        m_x = x;
        m_y = y;
    }

    virtual void on_click(std::function<void(click_data)> f)
    {
        m_on_click = f;
    }

    virtual void on_hover(std::function<void(bool)> f)
    {
        m_on_hover = f;
    }

    virtual void render() = 0;

  protected:
    engine::shader_program &m_shader;

    float m_x, m_y;
    bool m_hovered;
    glm::mat4 m_proj;
    float m_width, m_height;
    std::function<void(click_data)> m_on_click;
    std::function<void(bool)> m_on_hover;
};

class text_element : public ui_element
{
  public:
    text_element(shader_program &text_shader)
        : ui_element(text_shader)
        , m_text("O")
        , m_wrap(false)
    {
        m_texture =
            resource_manager::get_reference().get<engine::texture>("resources/textures/text/characters16x16.bmp");

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), m_data.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        update_data();

        m_shader.set_int("text", 0);
    }

    virtual ~text_element()
    {
    }

    virtual void render() override
    {
        m_shader.bind();
        m_shader.set_vec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        m_texture->bind();

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, m_data.size() / 4);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_shader.unbind();
        m_texture->unbind();
    }

    void set_wrap(const bool wrap)
    {
        m_wrap = wrap;
    }

    void set_text(const std::basic_string<char> &text)
    {
        m_text = text;
        update_data();
    }

    std::string get_text() const
    {
        return m_text;
    }

    void set_pos(const float x, const float y) override
    {
        ui_element::set_pos(x, y);
        update_data();
    }

    void update_data();

    // virtual void click(int button, int action) override
    // {
    //     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    //     {
    //         set_text("-");
    //     }
    //     else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    //     {
    //         set_text("+");
    //     }
    // }

  private:
    unsigned int m_vao, m_vbo;
    std::shared_ptr<engine::texture> m_texture;
    std::vector<float> m_data;
    std::string m_text;

    bool m_wrap;
};

}; // namespace engine
