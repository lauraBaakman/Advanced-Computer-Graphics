#include "mesh.h"

Mesh::Mesh(Obj *object, QObject *parent)
{
    qDebug() << "Mesh constructor:";
    addVertices(object);
    addEdges(object->getFaces());
}

void Mesh::add(Vertex *vertex)
{
    this->vertices.append(vertex);
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
        normal = &(vertexPositions[iterator.key()]);

        add(new Vertex(position, normal));
    }
}

void Mesh::addEdges(QMap<unsigned int, Obj::Face *> faces)
{

}

QDebug operator<<(QDebug stream, const Mesh &mesh)
{
    stream << "Mesh[ "                                             <<  &endl
           << "  vertexPositions:   ["  << mesh.vertexPositions    <<  &endl
           << "  vertexNormals:     ["  << mesh.vertexNormals      <<  &endl;
    stream << "vertexNormals: " << &endl;
    for(auto i : mesh.vertices){
        stream << *i;
    }
    stream << &endl;


    //           << "]"
    //           << &endl;
    return stream;
}
