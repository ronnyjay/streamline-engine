#pragma once

#include "assert.hpp"

#include <string>
#include <typeinfo>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

namespace engine
{

template <typename T> inline std::string demangle()
{
#if defined(__GNUC__) || defined(__clang__)
    int         status    = 0;
    char       *demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
    std::string result    = (status == 0) ? demangled : typeid(T).name();
    // remove namespace
    std::size_t idx = result.find_last_of(":");
    if (idx != std::string::npos)
    {
        result = result.substr(idx + 1, result.length());
    }
    std::free(demangled);
    return result;
#else
    return typeid(T).name();
#endif
}

template <typename T> class Singleton
{
  public:
    Singleton()
    {
        STREAMLINE_ASSERT(!m_instance, std::string("Instance of singleton previously created: ") + demangle<T>());
        m_instance = static_cast<T *>(this);
    }

    static T &getInstance()
    {
        STREAMLINE_ASSERT(m_instance, std::string("Instance of singleton does not exist: ") + demangle<T>());
        return *m_instance;
    }

    virtual ~Singleton()
    {
        STREAMLINE_ASSERT(m_instance, std::string("Instance of singleton previously deleted: ") + demangle<T>());
        m_instance = nullptr;
    }

  private:
    /** The singleton's instance */
    static T *m_instance;

    /** @brief Private copy constructor; forbidden. */
    Singleton(Singleton const &) = delete;

    /** @brief Private copy assignment operator; forbidden.  */
    Singleton &operator=(Singleton const &) = delete;
};

template <typename T> T *Singleton<T>::m_instance = nullptr;

} // namespace engine