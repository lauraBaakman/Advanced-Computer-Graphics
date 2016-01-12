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
            PHONG,
            NONE
        };
        Render::Mode renderMode;
        Render::Interpolation interpolationMode;
        Render::Illumination illuminationMode;
    };

    Render *render;

    class PnTriangle {
        public:
            float innerTessellationLevel;
            float outerTessellationLevel;
            bool visualizeGeometry;
    };

    static QMap<QString, QString> modelMap();
    static QPair<float, float> innerTessellationRange;
    static QPair<float, float> outerTessellationRange;
signals:
    void modelChanged(QString path);
    void renderModeChanged(Settings::Render::Mode);
    void settingsChanged(Settings *settings);

public slots:
    void onRenderModeChanged(int index);
    void onModelChanged(QString modelKey);
    void onIlluminationModeChanged(int index);
    void onShadingModeChanged(int index);
    void onVisualizeNormalsChanged(bool toggle);
//    void onInnerTessellationLevelChanged(float value);
//    void onOuterTessellationLevelChanged(float value);

private:

};

#endif // SETTINGS_H
