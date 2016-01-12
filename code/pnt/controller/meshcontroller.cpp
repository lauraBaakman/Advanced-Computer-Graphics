#include "meshcontroller.h"

MeshController::MeshController(QObject *parent) :
    QObject(parent),
    mesh(nullptr)
{

}

MeshController::~MeshController()
{
    delete mesh;
}

void MeshController::onModelChanged(QString modelPath)
{
    QFile file(modelPath);
    Obj *obj = Obj::fromFile(&file);
    if(this->mesh != nullptr) delete this->mesh;
    this->mesh = new Mesh(obj);
    delete obj;
    emit modelChanged(this->mesh);
}
