#include "meshcontroller.h"

MeshController::MeshController(Mesh *mesh, QObject *parent) :
    QObject(parent),
    mesh(mesh)
{

}
