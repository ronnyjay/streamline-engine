#pragma once

#include "engine/json/json.hpp"

const int DEFAULTRES = 800;
const int DEFAULTRESHEIGHT = 600;
const int DISPLAYMODE = 1;
const int MONITOR = 0;
const int VSYNC = 1;

const int FIRST_MOUSE = 1;
const int CAPTURE_MOUSE = 1;

const int SHOW_CURSOR = 0;
const int SHOW_WIREFRAMES = 0;
const int SHOW_COLLISIONS = 0;
const int SHOW_DEBUG_WINDOW = 0;
const int SHOW_DEBUG_METRICS = 0;

class config
{
  public:
    config();

    int defaultres = DEFAULTRES;
    int defaultresheight = DEFAULTRESHEIGHT;
    int displaymode = DISPLAYMODE;
    int monitor = MONITOR;
    int vsync = VSYNC;

    int first_mouse = FIRST_MOUSE;
    int capture_mouse = CAPTURE_MOUSE;

    int show_cursor = SHOW_CURSOR;
    int show_wireframes = SHOW_WIREFRAMES;
    int show_collisions = SHOW_COLLISIONS;
    int show_debug_window = SHOW_DEBUG_WINDOW;
    int show_debug_metrics = SHOW_DEBUG_METRICS;

    void from_json(const json_object &);
};