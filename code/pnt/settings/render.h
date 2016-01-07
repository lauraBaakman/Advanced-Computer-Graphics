#ifndef RENDER_H
#define RENDER_H

#include "settings/settings.h"

class Settings::Render {

public:
    enum Mode {
        POINTCLOUD,
        WIREFRAME,
        FLAT,
        PNTRIANGLES
    };

    Render();

    Mode getMode() const;
    void setMode(const Mode &value);

private:
    Mode mode;
};

#endif // RENDER_H
