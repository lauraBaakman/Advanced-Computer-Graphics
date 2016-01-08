#include "settings/settings.h"

Settings::Render::Mode Settings::Render::getMode() const
{
    return mode;
}

void Settings::Render::setMode(const Mode &value)
{
    mode = value;
}
