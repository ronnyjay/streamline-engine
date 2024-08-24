#pragma once

// clang-format off
enum event_type_e
{ 
  None, 
  KeyEvent, MouseEvent, 
  WindowResizeEvent, WindowCloseEvent
};
// clang-format on

class event
{
  public:
    inline const event_type_e type() const
    {
        return type_;
    }

    virtual ~event() = default;

  protected:
    event_type_e type_ = None;
};
