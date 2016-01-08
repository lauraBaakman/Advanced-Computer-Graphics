#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    this->render = new Render();
}

Settings::~Settings()
{
    delete render;
}

QMap<QString, QString> Settings::modelMap()
{
    QMap<QString, QString> modelMap;
    modelMap["Cube"] = "cube.obj";
    modelMap["Triangle"] = "triangle.obj";
    return modelMap;
}

void Settings::onRenderModeChanged(Settings::Render::Mode mode)
{   qDebug() << "RenderMode Changed";
    render->setMode(mode);
}
