#include "settings.h"

QPair<float, float> Settings::innerTessellationRange = QPair<float, float>(1.0, 12.0);
QPair<float, float> Settings::outerTessellationRange = QPair<float, float>(1.0, 12.0);

Settings::Settings(QObject *parent) : QObject(parent)
{
    this->render = new Render();
    this->pnTriangle = new PnTriangle();
}

Settings::~Settings()
{
    delete render;
    delete pnTriangle;
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
{
    render->renderMode = static_cast<Settings::Render::Mode>(index);
    emit settingsChanged();
}

void Settings::onModelChanged(QString modelKey)
{
    emit modelChanged(Settings::modelMap().value(modelKey));
}

void Settings::onIlluminationModeChanged(int index)
{
    render->illuminationModel = static_cast<Settings::Render::Illumination>(index);
    emit settingsChanged();
}

void Settings::onShadingModeChanged(int index)
{
    render->interpolationModel = static_cast<Settings::Render::Interpolation>(index);
    emit settingsChanged();
}

void Settings::onVisualizeNormalsChanged(bool toggle)
{
    render->visualizeNormals = toggle;
    emit settingsChanged();
}

void Settings::onInnerTessellationLevelChanged(float value)
{
    pnTriangle->innerTessellationLevel = value;
    emit settingsChanged();
}

void Settings::onOuterTessellationLevelChanged(float value)
{
    pnTriangle->outerTessellationLevel = value;
    emit settingsChanged();
}

void Settings::onVisualizeGeometryChanged(bool toggle)
{
    pnTriangle->visualizeGeometry = toggle;
    resetTessellationSliders();
    resetNormalCalculation();
    resetRenderUi();
    emit settingsChanged();
}

void Settings::resetTessellationSliders() {
    float tessellationLevel = 1.0;
    // because we need this and this is super informative ;)
    pnTriangle->innerTessellationLevel = tessellationLevel;
    pnTriangle->outerTessellationLevel = tessellationLevel;
    // Signal back to ui.
    emit tessellationLevelsChanged(tessellationLevel, tessellationLevel);
}

void Settings::resetNormalCalculation()
{
    pnTriangle->normalMode = Settings::PnTriangle::Normals::FAKE;
    emit normalCalculationChanged(static_cast<int>(pnTriangle->normalMode));
}

void Settings::resetRenderUi()
{
    render->renderMode = Settings::Render::Mode::WIREFRAME;
    render->illuminationModel = Settings::Render::Illumination::NONE;
    render->interpolationModel = Settings::Render::Interpolation::FLAT;
    render->visualizeNormals = false;

    emit renderUiChanged(static_cast<int>(render->renderMode),
                         static_cast<int>(render->illuminationModel),
                         static_cast<int>(render->interpolationModel),
                         render->visualizeNormals);
}

void Settings::onRenderPnTrianglesChanged(bool toggle)
{
    if(!toggle) {
        resetTessellationSliders();
        resetNormalCalculation();
    }
    emit settingsChanged();
}

void Settings::onNormalsChanged(int index)
{
    pnTriangle->normalMode = static_cast<Settings::PnTriangle::Normals>(index);
    emit settingsChanged();
}
