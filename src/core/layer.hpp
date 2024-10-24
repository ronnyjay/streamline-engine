#pragma once

#include "core/event.hpp"

namespace engine
{

/**
 * @brief
 *
 */
class Layer
{
  public:
    /**
     * @brief Default constructor
     *
     */
    Layer()
    {
    }

    /**
     * @brief Event callback
     *
     * @param e A reference to the Event
     */
    virtual void on_event(const Event &e) = 0;

    /**
     * @brief Default destructor
     *
     */
    virtual ~Layer()
    {
    }

  protected:
    /**
     * @brief Utility function for handling WindowResizedEvent's
     *
     * @param e
     */
    virtual void on_window_resize(const WindowResizeEvent &e) {};

    /**
     * @brief Utility function for handling KeyPressedEvent's
     *
     * @param e A reference to the KeyPressedEvent
     */
    virtual void on_key_press(const KeyPressEvent &e) {};

    /**
     * @brief Utility function for handling MousePresedEvent's
     *
     * @param e A reference to the MousePressedEvent
     */
    virtual void on_mouse_press(const MousePressEvent &e) {};

    /**
     * @brief Utility function for handling MouseMovedEvent's
     *
     * @param e A reference to the MouseMovedEvent
     */
    virtual void on_mouse_move(const MouseMoveEvent &e) {};

    /**
     * @brief Utility function for handling MouseScrolledEvent's
     *
     * @param e A reference to the MouseScrolledEvent
     */
    virtual void on_mouse_scroll(const MouseScrollEvent &e) {};
};

} // namespace engine