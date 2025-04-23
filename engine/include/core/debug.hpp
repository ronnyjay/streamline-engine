#pragma once

#include "core/settings.hpp"
#include "imgui.h"
#include "singleton.hpp"

namespace engine
{

// clang-format off
static const char *DisplayModes[] = {
  "Windowed",
  "Fullscreen",
  "Windowed Fullscreen"
};
// clang-format on

// clang-format off
static const char *Framerates[] = {
    "30 FPS",
    "60 FPS",
    "120 FPS",
    "144 FPS",
    "165 FPS",
    "240 FPS",
    "360 FPS",
    "Unlimited"
};
// clang-format on

struct DebugWindow : public Singleton<DebugWindow>
{
    bool b_showWindow  = false;
    bool b_showMetrics = false;

    DebugWindow();

    void draw();

    ~DebugWindow();

    bool hasPopupsOpen() const
    {
        if (ImGui::IsPopupOpen("Unsaved Changes", ImGuiPopupFlags_AnyPopup))
        {
            return true;
        }

        return false;
    }

    void closePopups()
    {
        if (ImGui::IsPopupOpen("Unsaved Changes", ImGuiPopupFlags_AnyPopup))
        {
            UserSettings::getInstance().discard();

            b_hideUnsavedChangesPopup = true;
        }
    }

  private:
    bool b_showUnsavedChangesPopup = false;
    bool b_hideUnsavedChangesPopup = false;

    struct VideoSettings
    {
        bool b_verticalSync  = true;
        int  monitorIndex    = 0;
        int  resolutionIndex = 0;
    } m_videoSettings;

    void drawDebugSettings();
    void drawVideoSettings();
    void drawSceneSettings();
};

} // namespace engine
