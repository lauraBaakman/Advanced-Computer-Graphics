#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    grabGesture(Qt::PinchGesture);
}

Canvas::~Canvas()
{

}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    initializeShaders();
    initializeBuffers();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);


}

void Canvas::constructModelViewProjectionMatrix()
{
    mvpMatrix.setToIdentity();
    mvpMatrix.scale(this->zoomingFactor);
    mvpMatrix.rotate(this->rotationAngle, 0.0, 0.0, 1.0);
}

bool Canvas::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture) {
          return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QWidget::event(event);
}

bool Canvas::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pinch = event->gesture(Qt::PinchGesture)) {
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    }
    return true;
}

void Canvas::pinchTriggered(QPinchGesture *gesture)
{
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if(changeFlags & QPinchGesture::ScaleFactorChanged) {
        this->zoomingFactor = gesture->scaleFactor();
    }
    if (gesture->state() == Qt::GestureFinished) {
        qDebug() << "Never happens?";
   }
    update();
}


