#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    Canvas();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    // Override event to get the gesture events
    bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // CANVAS_H
