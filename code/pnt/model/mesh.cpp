#include "mesh.h"

Mesh::Mesh(Obj *object, QObject *parent)
{
    addVertices(object);
    addEdges(object);
}

void Mesh::add(int key, Vertex *vertex)
{
    this->vertices.insert(key, vertex);
}

void Mesh::add(Edge *edge)
{
    this->edges.append(edge);
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

        add(iterator.key(), new Vertex(position, normal));
    }
}

void Mesh::addEdges(Obj *object)
{
    QMapIterator<unsigned int, Obj::Face*> iterator(object->getFaces());
    Edge *edge;
    while(iterator.hasNext()){
        iterator.next();
        for (int i = 0, j = 1; i < 3; i++, j = (i + 1) % 3){
            edge = new Edge(
                        this->vertices.value(iterator.value()->at(i)),
                        this->vertices.value(iterator.value()->at(j)));
            add(edge);
        }
    }
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
    for(auto i : mesh.edges){
        stream << *i;
    }
    stream << &endl;
    return stream;
}
