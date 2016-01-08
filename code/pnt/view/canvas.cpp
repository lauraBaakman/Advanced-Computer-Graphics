#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    grabGesture(Qt::PinchGesture);
}

Canvas::~Canvas()
{
    delete this->shaderProgram;
    delete this->vertexBuffer;
    delete this->normalBuffer;
    delete this->indexBuffer;
    this->vertexArrayObject.destroy();
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initializeShaders();
    initializeBuffers();
}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/resources/shaders/vertex_shader.vert");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/resources/shaders/fragment_shader.frag");
    this->shaderProgram->link();
}

void Canvas::initializeBuffers()
{
    this->vertexArrayObject.create();
    this->vertexArrayObject.bind();

    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->vertexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->vertexBuffer->create();
    this->vertexBuffer->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->normalBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->normalBuffer->create();
    this->normalBuffer->bind();

    this->indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    this->indexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->indexBuffer->create();
    this->indexBuffer->bind();

    this->vertexArrayObject.release();
}

void Canvas::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

void Canvas::updateBuffer(QOpenGLBuffer *buffer, QVector<unsigned int> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

void Canvas::updateBuffers(Mesh *model)
{
    updateBuffer(this->vertexBuffer, model->getVertexPositions());
    updateBuffer(this->normalBuffer, model->getVertexNormals());
    updateBuffer(this->indexBuffer, model->getIndexBuffer());
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!isAllocated(this->vertexBuffer)) {
        return;
    }

    this->shaderProgram->bind();
    this->vertexBuffer->bind();
    glPointSize(8.0f);
    glDrawArrays(GL_POINTS, 0, 8);
    this->vertexBuffer->release();
    this->shaderProgram->release();
}

bool Canvas::isAllocated(QOpenGLBuffer *buffer)
{
    return buffer->size() != 0;
}

void Canvas::constructModelViewProjectionMatrix()
{
    mvpMatrix.setToIdentity();

    // Scale determined by QPinchEvents
    mvpMatrix.scale(this->zoomingFactor);

    // Rotation along the axis determined by QDials in the ui.
    mvpMatrix.rotate(this->rotationAngles.x(), 1.0, 0.0, 0.0);
    mvpMatrix.rotate(this->rotationAngles.y(), 0.0, 1.0, 0.0);
    mvpMatrix.rotate(this->rotationAngles.z(), 0.0, 0.0, 1.0);
}

void Canvas::onRotationDialChanged(int axis, int value)
{
    this->rotationAngles[axis] = value;
    constructModelViewProjectionMatrix();
    update();
}

void Canvas::onModelChanged(Mesh *model)
{
    qDebug() << *model;
    updateBuffers(model);
    update();
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


