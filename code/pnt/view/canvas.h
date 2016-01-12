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
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "model/mesh.h"
#include "settings/settings.h"
#include "settings/material.h"
#include "settings/light.h"

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();

    void setSettings(Settings *value);

public slots:
    void onRotationDialChanged(int axis, int value);
    void onModelChanged(Mesh *model);
    void onRenderModeChanged(Settings::Render::Mode mode);
    void onSettingsChanged();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    // Override event to get the gesture events
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    // Shaders
    QOpenGLShaderProgram *shaderProgram;

    // Buffers
    QOpenGLBuffer *vertexBuffer;
    QOpenGLBuffer *normalBuffer;
    QOpenGLBuffer *indexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;

    bool isAllocated(QOpenGLBuffer *buffer);

    // OpenGL initialization
    void initializeShaders();
    void initializeBuffers();

    // OpenGL update
    int numIndices;
    int numVertices;
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<unsigned int> data);
    void updateBuffers(Mesh *model);

    // Transformation variables;
    QMatrix4x4 mvpMatrix;
    QVector3D rotationAngles;
    float zoomingFactor;
    void constructModelViewProjectionMatrix();
    void updateTransformationMatrix();

    // Set uniforms
    void setUniforms(Material material = Material(), Light light = Light());
    void setMaterialInShader(Material material);
    void setLightInShader(Light light);

    // Paint stuff
    Settings *settings;
    void drawWireframe();
    void drawShadedSurface();
    void drawPatches();

    // Events
    bool gestureEvent(QGestureEvent *event);
    void pinchTriggered(QPinchGesture *gesture);
};

#endif // CANVAS_H
