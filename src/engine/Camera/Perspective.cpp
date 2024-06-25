#include <engine/Application/Application.hpp>
#include <engine/Camera/Perspective.hpp>

using namespace engine;

extern Application application;

void PerspectiveCamera::Update()
{
    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

    m_ForwardHorizontal.x = cos(glm::radians(m_Yaw));
    m_ForwardHorizontal.y = 0;
    m_ForwardHorizontal.z = sin(glm::radians(m_Yaw));
    m_ForwardHorizontal = glm::normalize(m_ForwardHorizontal);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

glm::mat4 const PerspectiveCamera::ProjectionMatrix() const
{
    float aspectRatio = static_cast<float>(application.Width()) / static_cast<float>(application.Height());
    return glm::perspective(glm::radians(m_Zoom), aspectRatio, 0.1f, 1000.0f);
}

glm::mat4 const PerspectiveCamera::ViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void PerspectiveCamera::Move(const Direction direction, double timeStep)
{

    switch (direction)
    {
    case Forward:
        if (m_LockHorizontal)
        {
            m_Position += m_ForwardHorizontal * m_Speed * (float)timeStep;
        }
        else
        {
            m_Position += m_Front * m_Speed * (float)timeStep;
        }
        break;
    case Backward:
        if (m_LockHorizontal)
        {
            m_Position -= m_ForwardHorizontal * m_Speed * (float)timeStep;
        }
        else
        {
            m_Position -= m_Front * m_Speed * (float)timeStep;
        }
        break;
    case Left:
        m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed * (float)timeStep;
        break;
    case Right:
        m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed * (float)timeStep;
        break;
    case Up:
        m_Position.y += m_Speed * (float)timeStep;
        break;
    case Down:
        m_Position.y -= m_Speed * (float)timeStep;
        break;
    }

    Update();
}

void PerspectiveCamera::Move(double xPos, double yPos)
{
    xPos *= m_Sensitivity;
    yPos *= m_Sensitivity;

    m_Yaw += xPos;
    m_Pitch += yPos;

    if (m_Pitch > 89.0f)
    {
        m_Pitch = 89.0f;
    }

    if (m_Pitch < -89.0f)
    {
        m_Pitch = -89.0f;
    }

    Update();
}

void PerspectiveCamera::Move(double yOffset)
{
    m_Zoom -= yOffset;

    if (m_Zoom < 1.0f)
    {
        m_Zoom = 1.0f;
    }

    if (m_Zoom > 120.0f)
    {
        m_Zoom = 120.0f;
    }
}

void PerspectiveCamera::LockHorizontal(const bool lock)
{
    m_LockHorizontal = lock;
}

void PerspectiveCamera::DrawDebugInfo()
{
    Camera::DrawDebugInfo();

    ImGui::Text("Lock Horizontal");
    ImGui::SameLine();
    ImGui::Checkbox("##LockHorizontal", &m_LockHorizontal);
}