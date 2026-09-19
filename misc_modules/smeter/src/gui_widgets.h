#pragma once
#define GImGui (ImGui::GetCurrentContext())

#include <imgui/imgui.h>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <imgui/imgui_internal.h>
#include <gui/style.h>

#define SMETER_CELL_COUNT  9
#define SMETER_CELL_HEIGHT 24.0f
#define SMETER_CELL_GAP    4.0f
#define SMETER_CELL_GREEN  IM_COL32(0, 255, 0, 255)
#define SMETER_CELL_RED    IM_COL32(255, 0, 0, 255)

namespace ImGui {
    void SUnitsMeter(int sUnits) {
        ImGuiWindow* window = GetCurrentWindow();
        ImGuiStyle& style = GImGui->Style;

        ImVec2 min = window->DC.CursorPos;
        ImVec2 size = CalcItemSize(ImVec2(0, 0), CalcItemWidth(), 26);
        ImVec2 max = ImVec2(min.x + size.x, min.y + size.y);
        ImRect bb(min, max);

        ItemSize(size, style.FramePadding.y);

        if (!ItemAdd(bb, 0)) {
            return;
        }

        float indicatorCellGap = SMETER_CELL_GAP * style::uiScale;
        float totalWidthAvailable = size.x - min.x - (indicatorCellGap * SMETER_CELL_COUNT - 4);
        float indicatorCellWidth = (totalWidthAvailable / SMETER_CELL_COUNT) * style::uiScale;
        float indicatorCellHeight = SMETER_CELL_HEIGHT * style::uiScale;
        float indicatorCellStep = indicatorCellHeight / SMETER_CELL_COUNT;

        for (int i = 0; i < SMETER_CELL_COUNT; i++) {
            float currentXStart = i * indicatorCellWidth + (i * indicatorCellGap);
            float currentXEnd = currentXStart + indicatorCellWidth;

            ImVec2 rectStart = ImVec2(min.x + currentXStart, min.y + (SMETER_CELL_COUNT - 1 - i) * indicatorCellStep);
            ImVec2 rectEnd = ImVec2(min.x + currentXEnd, min.y + indicatorCellHeight);

            ImColor cellColor = i == SMETER_CELL_COUNT - 1 ? SMETER_CELL_RED : SMETER_CELL_GREEN;

            if (i + 1 <= sUnits) {
                window->DrawList->AddRectFilled(rectStart, rectEnd, cellColor, 0, 2.0f);
            }

            window->DrawList->AddRect(rectStart, rectEnd, cellColor, 0, 2.0f);
        }
    }
}

int calculateSUnitFromSignalStrength(float snr) {
    return round(snr / 6.0f);
}