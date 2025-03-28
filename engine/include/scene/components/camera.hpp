#pragma once

#include "transform.hpp" // IWYU pragma: keep

namespace engine
{

// clang-format off
enum class Projection
{
    Perspective, Orthographic
};
// clang-format on

struct Camera
{
    friend struct CameraSystem;

    static constexpr float PERSPECTIVE_NEAR_CLIP  = +0.1f;
    static constexpr float PERSPECTIVE_FAR_CLIP   = +1000.0f;
    static constexpr float PERSPECTIVE_ZOOM       = +90.0f;
    static constexpr float ORTHOGRAPHIC_NEAR_CLIP = -1.0f;
    static constexpr float ORTHOGRAPHIC_FAR_CLIP  = +1000.0f;
    static constexpr float ORTHOGRAPHIC_ZOOM      = +1.0f;

  private:
    Projection m_projection;

    float      m_perspNear;
    float      m_perspFar;
    float      m_perspZoom;

    float      m_orthoNear;
    float      m_orthoFar;
    float      m_orthoZoom;

    float      m_aspectRatio;

    mat4       m_viewMatrix;
    mat4       m_projectionMatrix;

  public:
    Camera(Projection proj = Projection::Perspective)
        : m_projection(proj)
    {
        m_perspNear   = PERSPECTIVE_NEAR_CLIP;
        m_perspFar    = PERSPECTIVE_FAR_CLIP;
        m_perspZoom   = PERSPECTIVE_ZOOM;
        m_orthoNear   = ORTHOGRAPHIC_NEAR_CLIP;
        m_orthoFar    = ORTHOGRAPHIC_FAR_CLIP;
        m_orthoZoom   = ORTHOGRAPHIC_ZOOM;
        m_aspectRatio = 4.0f / 3.0f;
    }

    bool       b_isPrimary       = false;
    bool       b_lockAspectRatio = false;

    Projection getProjection() const
    {
        return m_projection;
    }

    mat4 const &getProjectionMatrix()
    {
        return m_projectionMatrix;
    }

    mat4 const &getViewMatrix()
    {
        return m_viewMatrix;
    }

    float getZoom() const
    {
        switch (m_projection)
        {
        case Projection::Perspective:
            return m_perspZoom;
            break;
        case Projection::Orthographic:
            return m_orthoZoom;
            break;
        }
    }

    float getNearClip() const
    {
        switch (m_projection)
        {
        case Projection::Perspective:
            return m_perspNear;
            break;
        case Projection::Orthographic:
            return m_orthoNear;
            break;
        }
    }

    float getFarClip() const
    {
        switch (m_projection)
        {
        case Projection::Perspective:
            return m_perspFar;
            break;
        case Projection::Orthographic:
            return m_orthoFar;
            break;
        }
    }

    float getAspectRatio() const
    {
        return m_aspectRatio;
    }

    void setProjection(Projection projection)
    {
        m_projection = projection;
    }

    void setZoom(float val)
    {
        switch (m_projection)
        {
        case Projection::Perspective:
            m_perspZoom = val;
            break;
        case Projection::Orthographic:
            m_orthoZoom = val;
            break;
        }
    }

    void setNearClip(float val)
    {
        switch (m_projection)
        {
        case Projection::Perspective:
            m_perspNear = val;
            break;
        case Projection::Orthographic:
            m_orthoNear = val;
            break;
        }
    }

    void setFarClip(float val)
    {
        switch (m_projection)
        {
        case Projection::Perspective:
            m_perspFar = val;
            break;
        case Projection::Orthographic:
            m_orthoFar = val;
            break;
        }
    }

    void setAspectRatio(float width, float height)
    {
        m_aspectRatio = width / height;
    }
};

} // namespace engine
