#include "render.h"

Settings::Render::Render()
{

}

Settings::Render::Mode Settings::Render::getMode() const
{
    return this->mode;
}

void Settings::Render::setMode(const Settings::Render::Mode &value)
{
    this->mode = value;
}

