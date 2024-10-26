#pragma once

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