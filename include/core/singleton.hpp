#pragma once

#include "event.hpp"

#include <cassert>
#include <cstdio>

#include <memory> // IWYU pragma: keep

namespace engine
{

template <typename T>
class Singleton
{
  public:
    static T *GetInstancePtr()
    {
        return mInstance;
    }

    static T &GetInstance()
    {
        assert(mInstance);
        return (*mInstance);
    }

    virtual void Init() = 0;
    virtual void DeInit() = 0;

    virtual void OnEvent(Event &e) = 0;

    Singleton()
    {
        if (mInstance)
        {
            throw std::runtime_error("Instance of singleton created previously");
        }
        mInstance = static_cast<T *>(this);
    }

    virtual ~Singleton()
    {
        assert(mInstance);
        mInstance = nullptr;
    }

  protected:
    static T *mInstance;

  private:
    /** @brief Private copy constructor; forbidden. */
    Singleton(const Singleton &) = delete;

    /** @brief Private copy assignment operator; forbidden.  */
    Singleton &operator=(const Singleton &) = delete;
};

template <typename T>
T *Singleton<T>::mInstance = nullptr;

} // namespace engine
