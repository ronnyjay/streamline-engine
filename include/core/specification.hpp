#pragma once

#include <string>

namespace engine
{

class Application; // Forward Declaration

/**
 * @brief
 *
 */
class Specification
{
  public:
    static constexpr int DEFAULT_WINDOW_WIDTH  = 800;
    static constexpr int DEFAULT_WINDOW_HEIGHT = 600;

    /**
     * @brief
     *
     * @param application
     */
    virtual void OnInit(Application *const application) const;

    /**
     * @brief
     *
     * @param application
     */
    virtual void OnExit(Application *const application) const;

    /**
     * @brief
     *
     */
    virtual ~Specification() = default;
};

} // namespace engine