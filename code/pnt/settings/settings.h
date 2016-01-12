#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDebug>
#include <QPair>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    class Render {
    public:
        Render() {
            renderMode = Mode::WIREFRAME;
            interpolationModel = Interpolation::FLAT;
            illuminationModel = Illumination::NONE;
            visualizeNormals = false;
        }

        enum class Mode {
            WIREFRAME,
            SURFACE
        };
        enum class Interpolation {
            FLAT,
            PHONG,
            GOURAUD
        };
        enum class Illumination {
            NONE,
            PHONG
        };
        Render::Mode renderMode;
        Render::Interpolation interpolationModel;
        Render::Illumination illuminationModel;
        bool visualizeNormals;
    };

    Render *render;

    class PnTriangle {
    public:
        PnTriangle() {
            innerTessellationLevel = 1.0;
            outerTessellationLevel = 1.0;
            visualizeGeometry = false;
            normalMode = Normals::FAKE;
        }
        float innerTessellationLevel;
        float outerTessellationLevel;
        bool visualizeGeometry;

        enum class Normals {
            FAKE,
            REAl
        };
        PnTriangle::Normals normalMode;
    };

    PnTriangle *pnTriangle;

    static QMap<QString, QString> modelMap();
    static QPair<float, float> innerTessellationRange;
    static QPair<float, float> outerTessellationRange;
signals:
    void modelChanged(QString path);
    void renderModeChanged(Settings::Render::Mode);
    void settingsChanged();
    void tessellationLevelsChanged(float, float);
    void normalCalculationChanged(int);

public slots:
    void onRenderModeChanged(int index);
    void onModelChanged(QString modelKey);
    void onIlluminationModeChanged(int index);
    void onShadingModeChanged(int index);
    void onVisualizeNormalsChanged(bool toggle);
    void onInnerTessellationLevelChanged(float value);
    void onOuterTessellationLevelChanged(float value);
    void onVisualizeGeometryChanged(bool toggle);
    void onRenderPnTrianglesChanged(bool toggle);
    void onNormalsChanged(int index);

private:
    void resetTessellationSliders();
    void resetNormalCalculation();
};

#endif // SETTINGS_H
