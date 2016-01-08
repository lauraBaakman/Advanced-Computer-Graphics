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

    class Render;

signals:

public slots:
//    void onRenderModeChanged(Render::Mode mode);

private:
//    Render *render;

};

class Settings::Render {

};

#endif // SETTINGS_H
