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
    modelMap["Cube"] = ":/models/resources/models/cube.obj";
    return modelMap;
}

void Settings::onRenderModeChanged(Settings::Render::Mode mode)
{   qDebug() << "Settings::onRenderModeChanged" << mode;
    render->setMode(mode);
}

void Settings::onModelChanged(QString modelKey)
{
    qDebug() << "Settings::onModelChanged: " << modelKey;
    emit modelChanged(Settings::modelMap().value(modelKey));
}
