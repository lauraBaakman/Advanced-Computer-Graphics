#include "canvas.h"

Canvas::Canvas()
{
    grabGesture(Qt::PinchGesture);
}

void Canvas::initializeGL()
{
    qDebug() << "Implement";
}

void Canvas::paintGL()
{
    qDebug() << "Implement";
}

bool Canvas::event(QEvent *event)
{
    qDebug() << "Copy from ICS";
    return true;
}



