#include "edge.h"

Edge::Edge(Vertex *a, Vertex *b, QObject *parent):
    QObject(parent),
    a(a),
    b(b)
{}

QDebug operator<<(QDebug stream, const Edge &edge)
{
    stream << "Vertex ["
           << "\t a: "   << *(edge.a)  << &endl
           << "\t b: "     << *(edge.b)    << &endl
           << "]"                                   << &endl;
}
