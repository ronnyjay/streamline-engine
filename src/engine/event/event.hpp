#pragma once

// clang-format off
enum event_type
{ 
  None, 
  KeyEvent, MouseEvent, 
  WindowCloseEvent, WindowResizeEvent 
};
// clang-format on

class event
{
  public:
    inline const event_type type() const
    {
        return type_;
    }

    virtual ~event() = default;

  protected:
    event_type type_ = None;
};
