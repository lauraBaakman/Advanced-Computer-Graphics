#include "mesh.h"

Mesh::Mesh(Obj *object, QObject *parent):
    QObject(parent)
{
    addVertices(object);
    qDebug() << vertexPositions;
    qDebug() << vertexNormals;
}

void Mesh::addVertices(Obj *object)
{
    QVector3D* position;
    QVector3D* normal;

    QMapIterator<unsigned int, Obj::VertexPosition *> iterator(object->getVertexPositions());

    while (iterator.hasNext()) {
        iterator.next();

        vertexPositions.insert(iterator.key(), *(dynamic_cast<QVector3D*>((iterator.value()))));
        position = &(vertexPositions[iterator.key()]);

        vertexNormals.insert(iterator.key(), *(dynamic_cast<QVector3D*>(object->getVertexNormals().value(iterator.key()))));
        normal = &(vertexNormals[iterator.key()]);
    }
}

QDebug operator<<(QDebug stream, const Mesh &mesh)
{
    stream << "Mesh[ "                                             <<  &endl
           << "  vertexPositions:   ["  << mesh.vertexPositions    <<  &endl
           << "  vertexNormals:     ["  << mesh.vertexNormals      <<  &endl
           << "]";
    return stream;
}
