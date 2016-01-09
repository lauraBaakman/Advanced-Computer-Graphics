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
    modelMap["Cube"]        = ":/models/resources/models/cube.obj";
    modelMap["Cone"]        = ":/models/resources/models/cone.obj";
    modelMap["Suzanne"]     = ":/models/resources/models/monkey.obj";
    modelMap["Ico Sphere"]  = ":/models/resources/models/ico_sphere.obj";
    modelMap["Triangle"]    = ":/models/resources/models/triangle.obj";
    return modelMap;
}

void Settings::onRenderModeChanged(int index)
{   qDebug() << "Settings::onRenderModeChanged" << index;
    emit renderModeChanged(static_cast<Settings::Render::Mode>(index));
}

void Settings::onModelChanged(QString modelKey)
{
    qDebug() << "Settings::onModelChanged: " << modelKey;
    emit modelChanged(Settings::modelMap().value(modelKey));
}
