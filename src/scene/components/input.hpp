#pragma once

#include <glm/glm.hpp>

#include <functional>
#include <map>

namespace engine
{

enum class Axis
{
    MoveForward,
    MoveRight,
    Turn,
    LookUp
};

typedef enum
{
    A      = 65,
    B      = 66,
    C      = 67,
    D      = 68,
    E      = 69,
    F      = 70,
    G      = 71,
    H      = 72,
    I      = 73,
    J      = 74,
    K      = 75,
    L      = 76,
    M      = 77,
    N      = 78,
    O      = 79,
    P      = 80,
    Q      = 81,
    R      = 82,
    S      = 83,
    T      = 84,
    U      = 85,
    V      = 86,
    W      = 87,
    X      = 88,
    Y      = 89,
    Z      = 90,
    Space  = 32,
    LShift = 340,

    MouseX = 1023,
    MouseY = 1024,
} InputKey;

struct InputComponent
{
    /**
     * @brief
     *
     */
    InputComponent()
    {
        m_yaw   = 90.0f;
        m_pitch = 0.0f;
    }

    /**
     * @brief
     *
     * @param key
     * @param axis
     */
    void bind_key(Axis axis, InputKey key, float scale)
    {
        m_axis_inputs[axis].emplace_back(std::make_pair(key, scale));
    }

    /**
     * @brief
     *
     * @tparam T
     * @param axis
     * @param instance
     * @param function
     */
    template <typename T>
    void bind_axis(Axis axis, T *instance, void (T::*fn)(float))
    {
        m_axis_callbacks[axis] = std::bind(fn, instance, std::placeholders::_1);
    }

    /**
     * @brief
     *
     * @param value
     */
    void add_yaw_input(float value);

    /**
     * @brief
     *
     * @param value
     */
    void add_pitch_input(float value);

    /**
     * @brief
     *
     * @param direction
     * @param value
     */
    void add_movement_input(const glm::vec3 &direction, float value);

    /**
     * @brief
     *
     * @param value
     */
    void move_forward(float value);

    /**
     * @brief
     *
     * @param value
     */
    void move_backward(float value);

    /**
     * @brief
     *
     * @param value
     */
    void move_right(float value);

    /**
     * @brief
     *
     * @param value
     */
    void  move_left(float value);

    float yaw() const
    {
        return m_yaw;
    }

    float pitch() const
    {
        return m_pitch;
    }

    /**
     * @brief
     *
     * @return const glm::vec3&
     */
    const glm::vec3 &front() const
    {
        return m_front;
    }

    /**
     * @brief
     *
     * @return const glm::vec3&
     */
    const glm::vec3 &up() const
    {
        return m_up;
    }

    /**
     * @brief
     *
     * @return const glm::vec3&
     */
    const glm::vec3 &right() const
    {
        return m_right;
    }

    /**
     * @brief
     *
     * @return const glm::vec3&
     */
    const glm::vec3 &position() const
    {
        return m_position;
    }

    /**
     * @brief
     *
     * @return const std::map<Axis, InputKey>&
     */
    const std::map<Axis, std::vector<std::pair<InputKey, float>>> &axis_inputs() const
    {
        return m_axis_inputs;
    }

    /**
     * @brief
     *
     * @return const std::map<Axis, std::function<void()>>&
     */
    const std::map<Axis, std::function<void(float)>> &axis_callbacks() const
    {
        return m_axis_callbacks;
    }

  private:
    float                                                   m_yaw;
    float                                                   m_pitch;

    glm::vec3                                               m_front;
    glm::vec3                                               m_up;
    glm::vec3                                               m_right;

    glm::vec3                                               m_position;

    std::map<Axis, std::vector<std::pair<InputKey, float>>> m_axis_inputs;
    std::map<Axis, std::function<void(float)>>              m_axis_callbacks;

    void                                                    update_control_rotation();
};

} // namespace engine