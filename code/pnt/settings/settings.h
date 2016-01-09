#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDebug>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    class Render {
    public:
        enum Mode {
            POINTCLOUD,
            WIREFRAME,
            NORMALS
        };
    };

    static QMap<QString, QString> modelMap();
signals:
    void modelChanged(QString path);
    void renderModeChanged(Settings::Render::Mode);

public slots:
    void onRenderModeChanged(int index);
    void onModelChanged(QString modelKey);

private:
    Render *render;
};

#endif // SETTINGS_H
