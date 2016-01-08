#include "vertex.h"

Vertex::Vertex(QVector3D *location, QVector3D *normal, QObject *parent):
    QObject(parent),
    location(location),
    normal(normal)
{

}

QDebug operator<<(QDebug stream, const Vertex &vertex)
{
    stream << "Vertex ["
           << "\t location: "   << *(vertex.location)  << &endl
           << "\t normal: "     << *(vertex.normal)    << &endl
           << "]"                                   << &endl;
}


