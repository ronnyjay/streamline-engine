#include <engine/user_interface/ui_element.hpp>

using namespace engine;

void text_element::update_data()
{
    m_data.clear();

    float padding = 0.005f;

    float dx = 1.0f / 32.0f;
    float dy = 1.0f / 16.0f;

    float du = 1.0f / 32.0f;
    float dv = -1.0f / 4.0f;

    m_width = m_text.size() * (dx + padding);
    m_height = dy;

    float x = m_x - m_width / 2;
    float y = m_y - m_height / 2;

    for (char c : m_text)
    {
        float u, v;

        u = (c % 32) / 32.0f;
        v = 1.0f - (((int)c / 32) / 4.0f);

        // bottom left
        m_data.push_back(x);
        m_data.push_back(y);

        m_data.push_back(u);
        m_data.push_back(v);

        // bottom right
        m_data.push_back(x + dx);
        m_data.push_back(y);

        m_data.push_back(u + du);
        m_data.push_back(v);

        // top left
        m_data.push_back(x);
        m_data.push_back(y + dy);

        m_data.push_back(u);
        m_data.push_back(v + dv);

        // top right
        m_data.push_back(x + dx);
        m_data.push_back(y + dy);

        m_data.push_back(u + du);
        m_data.push_back(v + dv);

        x += (dx + padding);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), m_data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
