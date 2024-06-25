#include <engine/Application/Application.hpp>
#include <engine/Camera/Orthographic.hpp>

using namespace engine;

extern Application application;

void OrthographicCamera::Update()
{
    m_ViewModel = glm::mat4(1.0f);
    m_ViewModel = glm::translate(m_ViewModel, m_Position);
    m_ViewModel = glm::rotate(m_ViewModel, glm::radians(m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ViewModel = glm::rotate(m_ViewModel, glm::radians(m_Pitch), glm::vec3(1.0, 0.0f, 0.0f));
    m_ViewModel = glm::inverse(m_ViewModel);
}

glm::mat4 const OrthographicCamera::ProjectionMatrix() const
{
    float aspectRatio = static_cast<float>(application.Width()) / static_cast<float>(application.Height());

    float left = -2.0f * aspectRatio * m_Zoom;
    float right = 2.0f * aspectRatio * m_Zoom;
    float bottom = -2.0f * m_Zoom;
    float top = 2.0f * m_Zoom;

    return glm::ortho(left, right, bottom, top, -1.0f, 1000.0f);
}

glm::mat4 const OrthographicCamera::ViewMatrix() const
{
    return ProjectionMatrix() * m_ViewModel;
}

void OrthographicCamera::Move(const Direction direction, double timeStep)
{
    switch (direction)
    {
    case Forward:
        m_Position.z += m_Speed * timeStep;
        break;
    case Backward:
        m_Position.z -= m_Speed * timeStep;
        break;
    case Left:
        m_Position.x -= m_Speed * timeStep;
        break;
    case Right:
        m_Position.x += m_Speed * timeStep;
        break;
    case Up:
        m_Position.y += m_Speed * timeStep;
        break;
    case Down:
        m_Position.y -= m_Speed * timeStep;
        break;
    }

    Update();
}
