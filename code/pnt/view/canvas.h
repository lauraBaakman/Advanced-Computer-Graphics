#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QGestureEvent>
#include <QPinchGesture>
#include <QMatrix4x4>
#include <QVector3D>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();

public slots:
    void onRotationDialChanged(int axis, int value);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    // Override event to get the gesture events
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:

    // OpenGL initialization
    void initializeShaders();
    void initializeBuffers();

    // Transformation variables;
    QMatrix4x4 mvpMatrix;
    QVector3D rotationAngles;
    float zoomingFactor;
    void constructModelViewProjectionMatrix();

    // Events
    bool gestureEvent(QGestureEvent *event);
    void pinchTriggered(QPinchGesture *gesture);
};

#endif // CANVAS_H
