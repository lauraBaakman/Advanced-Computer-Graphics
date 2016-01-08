#ifndef RENDER_H
#define RENDER_H

#include "settings/settings.h"

class Settings::Render {

public:
    enum Mode {
        POINTCLOUD,
        WIREFRAME,
        FLAT,
        PHONG
    };

    Render();

    Settings::Render::Mode getMode() const;
    void setMode(const Settings::Render::Mode &value);

private:
    Settings::Render::Mode mode;
};

#endif // RENDER_H
