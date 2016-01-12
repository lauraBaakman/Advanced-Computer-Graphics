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
            POINTCLOUD,
            WIREFRAME,
            SURFACE
        };
        enum class Illumination {
            FLAT,
            PHONG,
            GOURAUD
        };
        enum class Shading {
            PHONG,
            NONE
        };
    };

    static QMap<QString, QString> modelMap();
    static QPair<float, float> innerTessellationRange;
    static QPair<float, float> outerTessellationRange;
signals:
    void modelChanged(QString path);
    void renderModeChanged(Settings::Render::Mode);

public slots:
    void onRenderModeChanged(int index);
    void onModelChanged(QString modelKey);
    void onIlluminationModeChanged(int index);
    void onShadingModeChanged(int index);
    void onVisualizeNormalsChanged(bool toggle);

private:
    Render *render;
};

#endif // SETTINGS_H
