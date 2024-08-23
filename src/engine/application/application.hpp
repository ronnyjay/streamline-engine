#pragma once

class application
{

  public:
    static application &get_reference()
    {
        if (!ref)
            ref = new application;

        return *ref;
    }

    static void reset()
    {
        delete ref;
        ref = nullptr;
    }

    application() = default;
    ~application() = default;

    application(const application &) = delete;
    application(application &&) = delete;

    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

  private:
    static application *ref;
};
