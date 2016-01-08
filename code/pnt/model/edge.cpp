#include "edge.h"

Edge::Edge(Vertex *a, Vertex *b, QObject *parent):
    QObject(parent),
    a(a),
    b(b)
{}

QDebug operator<<(QDebug stream, const Edge &edge)
{
    stream << "Edge ["
           << *(edge.a->getLocation())
           << "\t"
           << *(edge.b->getLocation())
           << "]" << &endl;
    return stream;
}
