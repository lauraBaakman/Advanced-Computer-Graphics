#include "mesh.h"

Mesh::Mesh(Obj *object, QObject *parent)
{
    addVertices(object);
    addEdges(object);

    for(auto v : vertices){
        qDebug() << *v;
    }

    for(auto vn : vertexNormals){
        qDebug() << &vn;
    }
    exit(-1);
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
    Vertex* vertex;

    QMapIterator<unsigned int, Obj::VertexPosition *> iterator(object->getVertexPositions());

    while (iterator.hasNext()) {
        iterator.next();

        vertexPositions.insert(iterator.key(), *(dynamic_cast<QVector3D*>((iterator.value()))));
        position = &(vertexPositions[iterator.key()]);

        vertexNormals.insert(iterator.key(), *(dynamic_cast<QVector3D*>(object->getVertexNormals().value(iterator.key()))));
        normal = &(vertexNormals[iterator.key()]);

        vertex = new Vertex(position, normal);

        qDebug() << "position pointer:  " << position;
        qDebug() << "normal pointer:    " << normal;
        qDebug() << "vertex:            " << *vertex;
        exit(-1);

        add(iterator.key(), vertex);
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
        for(int i = 0, j = 0; i < 3; i++, j = (i + 1) % 3){
            edge = new Edge(
                        vertices.value(face->value(i)),
                        vertices.value(face->value(j)));
            add(edge);
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
