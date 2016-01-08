#include "meshcontroller.h"

MeshController::MeshController(Mesh *mesh, QObject *parent) :
    QObject(parent),
    mesh(mesh)
{

}

MeshController::~MeshController()
{
    delete grid;
}

void MeshController::onModelChanged(QString modelPath)
{
    qDebug() << "MeshController::onModelChanged(QString modelPath): " << modelPath;
}
