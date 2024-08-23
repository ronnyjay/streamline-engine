#pragma once

#include "event.hpp"

class key_event : public event
{
  public:
    key_event(unsigned int key, unsigned int scancode, unsigned int action, unsigned int mods)
        : key_(key)
        , scancode_(scancode)
        , action_(action)
        , mods_(mods)
    {
        type_ = KeyEvent;
    }

    inline unsigned int key() const
    {
        return key_;
    }

    inline unsigned int scancode() const
    {
        return scancode_;
    }

    inline unsigned int action() const
    {
        return action_;
    }

    inline unsigned int mods() const
    {
        return mods_;
    }

  private:
    unsigned int key_;
    unsigned int scancode_;
    unsigned int action_;
    unsigned int mods_;
};