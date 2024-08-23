#pragma once

#include <engine/Camera/Camera.hpp>
#include <engine/Camera/Orthographic.hpp>
#include <engine/Camera/Perspective.hpp>

namespace engine
{

typedef enum
{
    Perspective,
    Orthographic,
} CameraType;

class PlayerCamera
{
  public:
    PlayerCamera(CameraType type)
    {
        m_Perspective = new PerspectiveCamera();
        m_Orthographic = new OrthographicCamera();

        SetType(type);
    }

    PlayerCamera(const PlayerCamera &) = default;

    void SetType(CameraType type)
    {
        switch (type)
        {
        case Perspective:
            camera = m_Perspective;
            break;
        case Orthographic:
            camera = m_Orthographic;
            break;
        }
    }

    Camera *camera;

    int offset = 1.0f;

    ~PlayerCamera()
    {

        delete m_Perspective;
        delete m_Orthographic;
    }

  private:
    CameraType m_Type;
    PerspectiveCamera *m_Perspective;
    OrthographicCamera *m_Orthographic;
};

} // namespace engine