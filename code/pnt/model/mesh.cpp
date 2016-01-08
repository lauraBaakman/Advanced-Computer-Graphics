#include "mesh.h"

Mesh::Mesh(Obj *object, QObject *parent):
    QObject(parent)
{
    addVertices(object);
    addEdges(object);
}

void Mesh::addVertices(Obj *object)
{
    QVector3D* position;
    QVector3D* normal;
    Vertex* vertex;

    QMapIterator<unsigned int, Obj::VertexPosition *> iterator(object->getVertexPositions());

    qDebug() << "in addVertices:" << &endl;

    while (iterator.hasNext()) {
        iterator.next();

        vertexPositions.insert(iterator.key(), *(dynamic_cast<QVector3D*>((iterator.value()))));
        position = &(vertexPositions[iterator.key()]);

        vertexNormals.insert(iterator.key(), *(dynamic_cast<QVector3D*>(object->getVertexNormals().value(iterator.key()))));
        normal = &(vertexNormals[iterator.key()]);

        vertex = new Vertex(position, normal);

        vertices.insert(iterator.key(), vertex);
    }
}

void Mesh::addEdges(Obj *object)
{
    QMapIterator<unsigned int, Obj::Face*> iterator(object->getFaces());
    Obj::Face* face;
    while(iterator.hasNext()){
        iterator.next();
        Edge* edge;
        face = iterator.value();
        for(int i = 0, j = 1; i < 3; i++, j = (i + 1) % 3){
            edge = new Edge(
                        vertices.value(face->value(i)),
                        vertices.value(face->value(j)));
            edges.append(edge);
        }
    }
}

QDebug operator<<(QDebug stream, const Mesh &mesh)
{
    stream << "Mesh[ "                                             <<  &endl
           << "  vertexPositions:   ["  << mesh.vertexPositions    <<  &endl
           << "  vertexNormals:     ["  << mesh.vertexNormals      <<  &endl;
    stream << "vertices: " << &endl;
    for(auto i : mesh.vertices){
        stream << *i;
    }
    stream << &endl;
    for(auto i : mesh.edges){
        stream << *i;
    }
    stream << &endl;
    return stream;
}
