#include "settings.h"

QPair<float, float> Settings::innerTessellationRange = QPair<float, float>(1.0, 12.0);
QPair<float, float> Settings::outerTessellationRange = QPair<float, float>(1.0, 12.0);

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
    modelMap["Cube"]            = ":/models/resources/models/cube.obj";
    modelMap["Cone"]            = ":/models/resources/models/cone.obj";
    modelMap["Suzanne"]         = ":/models/resources/models/monkey.obj";
    modelMap["Laurana"]         = ":/models/resources/models/Laurana50k.obj";
    modelMap["Ico Sphere"]      = ":/models/resources/models/ico_sphere.obj";
    modelMap["Triangle"]        = ":/models/resources/models/triangle.obj";
    modelMap["Quake Dog"]       = ":/models/resources/models/dog.obj";
    modelMap["Vore"]            = ":/models/resources/models/shalrath.obj";
    modelMap["Shambler"]        = ":/models/resources/models/shambler.obj";
    modelMap["Enforcer"]        = ":/models/resources/models/enforcer.obj";
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
