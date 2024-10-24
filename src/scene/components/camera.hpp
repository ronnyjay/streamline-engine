#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

namespace engine
{

enum class Projection
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

struct CameraComponent
{
    static constexpr float NEAR_CLIP    = 0.1f;

    static constexpr float FAR_CLIP     = 1000.0f;

    static constexpr float FOV          = 90.0f;

    static constexpr float ASPECT_RATIO = 4.0f / 3.0f;

    /**
     * @brief
     *
     * @param proj
     */
    CameraComponent(Projection proj = Projection::PERSPECTIVE)
        : m_projection_type(proj)
    {
        m_near              = NEAR_CLIP;
        m_far               = FAR_CLIP;
        m_fov               = FOV;
        m_ratio             = ASPECT_RATIO;

        m_yaw               = 90.0f;
        m_pitch             = 0.0f;

        m_front             = glm::vec3(0.0f);
        m_up                = glm::vec3(0.0f);
        m_right             = glm::vec3(0.0f);

        m_position          = glm::vec3(0.0f);

        m_view_matrix       = glm::mat4(0.0f);
        m_projection_matrix = glm::mat4(0.0f);

        update_view_matrix();
        update_projection_matrix();
    }

    bool is_primary        = false;

    bool lock_aspect_ratio = false;

    /**
     * @brief
     *
     * @param proj
     */
    void set_projection(Projection proj);

    /**
     * @brief
     *
     * @param near
     */
    void set_near(float near);

    /**
     * @brief
     *
     * @param far
     */
    void set_far(float far);

    /**
     * @brief
     *
     * @param fov
     */
    void set_fov(float fov);

    /**
     * @brief
     *
     * @param yaw
     */
    void set_yaw(float yaw);

    /**
     * @brief
     *
     * @param pitch
     */
    void set_pitch(float pitch);

    /**
     * @brief
     *
     * @param position
     */
    void set_position(const glm::vec3 &position);

    /**
     * @brief
     *
     * @param ratio
     */
    void set_aspect_ratio(uint16_t width, uint16_t height);

    /**
     * @brief
     *
     * @return const glm::mat4&
     */
    const glm::mat4 &view_matrix() const
    {
        return m_view_matrix;
    }

    /**
     * @brief
     *
     * @return const glm::mat4&
     */
    const glm::mat4 &projection_matrix() const
    {
        return m_projection_matrix;
    }

    /**
     * @brief
     *
     * @return const glm::mat4
     */
    const glm::mat4 view_projection_matrix() const
    {
        return m_view_matrix * m_projection_matrix;
    }

  private:
    Projection m_projection_type;

    float      m_near;
    float      m_far;
    float      m_fov;
    float      m_ratio;

    float      m_yaw;
    float      m_pitch;

    glm::vec3  m_front;
    glm::vec3  m_up;
    glm::vec3  m_right;

    glm::vec3  m_position;

    glm::mat4  m_view_matrix;
    glm::mat4  m_projection_matrix;

    void       update_view_matrix();
    void       update_projection_matrix();
};

} // namespace engine