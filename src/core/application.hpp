#pragma once

#include <memory>

namespace engine
{

class Application
{
  public:
    static Application &get();

    void run();

  private:
    Application()
    {
    }

    static std::unique_ptr<Application> kInstance;
};

} // namespace engine
