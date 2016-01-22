#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    grabGesture(Qt::PinchGesture);
}

Canvas::~Canvas()
{
    this->vertexBuffer->destroy();
    this->normalBuffer->destroy();
    this->indexBuffer->destroy();
    this->vertexArrayObject.destroy();
    delete this->shaderProgram;
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    initializeShaders();
    initializeBuffers();
}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/resources/shaders/vertex.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/shaders/resources/shaders/controll.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/shaders/resources/shaders/evaluation.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/resources/shaders/geometry.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/resources/shaders/fragment.glsl");
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

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

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
    this->numVertices = model->getVertexPositions().size();
    updateBuffer(this->vertexBuffer, model->getVertexPositions());

    updateBuffer(this->normalBuffer, model->getVertexNormals());

    this->numIndices = model->getIndexBuffer().size();
    updateBuffer(this->indexBuffer, model->getIndexBuffer());
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!isAllocated(this->vertexBuffer)) {
        return;
    }

    this->shaderProgram->bind();
    this->vertexArrayObject.bind();

    //Should be placed in correct spot
    setUniforms();

    updateTransformationMatrix();

    switch(this->settings->render->renderMode) {
    case Settings::Render::Mode::WIREFRAME:
        drawWireframe();
        break;
    case Settings::Render::Mode::SURFACE:
        drawShadedSurface();
    }

    this->vertexArrayObject.release();
    this->shaderProgram->release();
}

bool Canvas::isAllocated(QOpenGLBuffer *buffer)
{
    return buffer->size() != 0;
}

void Canvas::updateTransformationMatrix()
{
    constructModelViewProjectionMatrix();
    this->shaderProgram->setUniformValue("mvpMatrix", this->mvpMatrix);
    this->shaderProgram->setUniformValue("normalMatrix", this->normalMatrix);
}

void Canvas::resetZoomAndRotation()
{
//    this->zoomingFactor = 1.0;
    this->rotationAngles = QVector3D(1.0, 1.0, 1.0);
}

void Canvas::setUniforms(Material material, Light light)
{
    setMaterialInShader(material);
    setLightInShader(light);
    setTessellationLevels(this->settings->pnTriangle->innerTessellationLevel,
                          this->settings->pnTriangle->outerTessellationLevel);

    setShadingModel(this->settings->render->interpolationModel, this->settings->pnTriangle->visualizeGeometry);
    setIlluminationModel(this->settings->render);
    setNormalComputationMethod(this->settings->pnTriangle->normalMode);
//    setNormalComputationMethod(Settings::PnTriangle::Normals::FAKE);
}

void Canvas::setMaterialInShader(Material material)
{
    shaderProgram->setUniformValue("material.specularReflectionConstant", material.specularReflectionConstant);
    shaderProgram->setUniformValue("material.diffuseReflectionConstant", material.diffuseReflectionConstant);
    shaderProgram->setUniformValue("material.ambientReflectionConstant", material.ambientReflectionConstant);
    shaderProgram->setUniformValue("material.alfa", material.alfa);
    shaderProgram->setUniformValue("material.color", material.color);
}

void Canvas::setLightInShader(Light light)
{
    shaderProgram->setUniformValue("light.position", light.position);
    shaderProgram->setUniformValue("light.ambientLightIntensity", light.ambientIntensity);
    shaderProgram->setUniformValue("light.diffuseLightIntensity", light.diffuseIntensity);
    shaderProgram->setUniformValue("light.specularLightIntensity", light.specularIntensity);
}

void Canvas::setTessellationLevels(float inner, float outer)
{
    shaderProgram->setUniformValue("innerTessellationLevel", inner);
    shaderProgram->setUniformValue("outerTessellationLevel", outer);
}

void Canvas::setIlluminationModel(Settings::Render* renderSettings)
{
    GLuint functionIndex;
    if(renderSettings->visualizeNormals){
        functionIndex = glGetSubroutineIndex(shaderProgram->programId(), GL_FRAGMENT_SHADER, "visualizeNormals");
    } else {
        switch(renderSettings->illuminationModel){
        case Settings::Render::Illumination::NONE:
            functionIndex = glGetSubroutineIndex(shaderProgram->programId(), GL_FRAGMENT_SHADER, "noShading");
            break;
        case Settings::Render::Illumination::PHONG:
            functionIndex = glGetSubroutineIndex(shaderProgram->programId(), GL_FRAGMENT_SHADER, "phongReflection");
            break;
        }
    }
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &functionIndex);
}

void Canvas::setNormalComputationMethod(Settings::PnTriangle::Normals mode)
{
    GLuint functionIndex;
    switch(mode){
    case Settings::PnTriangle::Normals::FAKE:
        functionIndex = glGetSubroutineIndex(shaderProgram->programId(), GL_TESS_EVALUATION_SHADER, "interpolateFakeNormals");
        break;
    case Settings::PnTriangle::Normals::REAl:
        functionIndex = glGetSubroutineIndex(shaderProgram->programId(), GL_TESS_EVALUATION_SHADER, "interpolateRealNormals");
        break;
    }
    glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &functionIndex);
}

void Canvas::setShadingModel(Settings::Render::Interpolation mode, bool showGeometricComponent)
{
    int interpolationMode;
    if(showGeometricComponent){
        interpolationMode = 3;
    } else {
        switch(mode){
        case Settings::Render::Interpolation::PHONG:
            interpolationMode = 1;
            break;
        case Settings::Render::Interpolation::FLAT:
            interpolationMode = 2;
            break;
        case Settings::Render::Interpolation::GOURAUD:
            interpolationMode = 4;
            break;
        }
    }
    shaderProgram->setUniformValue("interpolationMode", interpolationMode);
}

void Canvas::setSettings(Settings *value)
{
    settings = value;
}

void Canvas::drawWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawPatches();
}

void Canvas::drawShadedSurface()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawPatches();
}

void Canvas::drawPatches()
{
    glDrawElements(GL_PATCHES, this->numIndices, GL_UNSIGNED_INT, (void*)(0));
}

void Canvas::constructModelViewProjectionMatrix()
{
    mvpMatrix.setToIdentity();

    // Rotation along the axis determined by QDials in the ui.
    mvpMatrix.rotate(this->rotationAngles.x(), 1.0, 0.0, 0.0);
    mvpMatrix.rotate(this->rotationAngles.y(), 0.0, 1.0, 0.0);
    mvpMatrix.rotate(this->rotationAngles.z(), 0.0, 0.0, 1.0);

    // Scale determined by QPinchEvents
    mvpMatrix.scale(this->zoomingFactor);

    normalMatrix = mvpMatrix.normalMatrix();
}

void Canvas::onRotationDialChanged(int axis, int value)
{
    this->rotationAngles[axis] = value;
    update();
}

void Canvas::onModelChanged(Mesh *model)
{
    this->resetZoomAndRotation();
    updateBuffers(model);
    update();
}

void Canvas::onSettingsChanged()
{
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


