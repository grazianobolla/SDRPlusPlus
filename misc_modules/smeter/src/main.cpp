#define GImGui (ImGui::GetCurrentContext())

#include <imgui.h>
#include <module.h>
#include <gui/gui.h>
#include <gui/style.h>
#include <gui/widgets/volume_meter.h>
#include "gui_widgets.h"

SDRPP_MOD_INFO{
    /* Name:            */ "smeter",
    /* Description:     */ "Show signal strength in S-units",
    /* Author:          */ "CX2EG",
    /* Version:         */ 0, 1, 0,
    /* Max instances    */ -1
};

class SMeterModule : public ModuleManager::Instance {
public:
    SMeterModule(std::string name) {
        this->name = name;
        gui::menu.registerEntry(name, menuHandler, this, NULL);
    }

    ~SMeterModule() {
        gui::menu.removeEntry(name);
    }

    void postInit() {}

    void enable() {
        enabled = true;
    }

    void disable() {
        enabled = false;
    }

    bool isEnabled() {
        return enabled;
    }

private:
    static void menuHandler(void* ctx) {
        SMeterModule* _this = (SMeterModule*)ctx;
        ImGui::FillWidth();

        int sUnits = calculateSUnitFromSignalStrength(gui::waterfall.selectedVFOSNR);
        ImGui::SUnitsMeter(sUnits);
    }

    std::string name;
    bool enabled = true;
};

MOD_EXPORT void _INIT_() {
    // Nothing here
}

MOD_EXPORT ModuleManager::Instance* _CREATE_INSTANCE_(std::string name) {
    return new SMeterModule(name);
}

MOD_EXPORT void _DELETE_INSTANCE_(void* instance) {
    delete (SMeterModule*)instance;
}

MOD_EXPORT void _END_() {
    // Nothing here
}