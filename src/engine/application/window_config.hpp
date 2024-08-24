#pragma once

#include "libstreamline/debug/logger.hpp"
#include <cstring>
#include <source_location>

#include <libstreamline/exception/exception.hpp>
#include <libstreamline/json/json.hpp>
#include <string>
#include <unordered_map>

typedef enum
{
    FULLSCREEN,
    WINDOWED,
    BORDERLESS
} display_mode_e;

const std::unordered_map<display_mode_e, std::string> display_modes_strings = {
    {FULLSCREEN, "Fullscreen"}, {WINDOWED, "Windowed"}, {BORDERLESS, "Fullscreen Borderless"}};

typedef enum
{
    FPS_30 = 30,
    FPS_60 = 60,
    FPS_120 = 120,
    FPS_144 = 144,
    FPS_165 = 165,
    FPS_240 = 240,
    FPS_360 = 360,
    FPS_UNLIMITED
} framerate_e;

struct window_config
{
    window_config()
    {
    }

    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    int display_mode = DEFAULT_DISPLAYMODE;
    std::string monitor = DEFAULT_MONITOR;
    int vsync = DEFAULT_VSYNC;

    int first_mouse = DEFAULT_FIRST_MOUSE;
    int capture_mouse = DEFAULT_CAPTURE_MOUSE;

    int show_cursor = DEFAULT_SHOW_CURSOR;
    int show_wireframes = DEFAULT_SHOW_WIREFRAMES;
    int show_collisions = DEFAULT_SHOW_COLLISIONS;
    int show_debug_window = DEFAULT_SHOW_DEBUG_WINDOW;
    int show_debug_metrics = DEFAULT_SHOW_DEBUG_METRICS;

    void export_to_file()
    {
        throw unimplemented_exception(std::source_location::current());
    }

    void load(const json_object &o);

  private:
    static logger log;

    static constexpr int DEFAULT_WIDTH = 800;
    static constexpr int DEFAULT_HEIGHT = 600;
    static constexpr int DEFAULT_DISPLAYMODE = display_mode_e::WINDOWED;
    static constexpr std::string DEFAULT_MONITOR = "";
    static constexpr bool DEFAULT_VSYNC = true;

    static constexpr bool DEFAULT_FIRST_MOUSE = true;
    static constexpr bool DEFAULT_CAPTURE_MOUSE = true;

    static constexpr bool DEFAULT_SHOW_CURSOR = false;
    static constexpr bool DEFAULT_SHOW_WIREFRAMES = false;
    static constexpr bool DEFAULT_SHOW_COLLISIONS = false;
    static constexpr bool DEFAULT_SHOW_DEBUG_WINDOW = false;
    static constexpr bool DEFAULT_SHOW_DEBUG_METRICS = false;
};
