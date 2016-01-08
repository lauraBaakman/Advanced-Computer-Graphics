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

            };
         Mode mode;

         Mode getMode() const;
         void setMode(const Mode &value);
    };

signals:

public slots:
    void onRenderModeChanged(Settings::Render::Mode mode);

private:
    Render *render;

};

#endif // SETTINGS_H
