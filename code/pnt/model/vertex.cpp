#include "vertex.h"

Vertex::Vertex(QVector3D *location, QVector3D *normal, QObject *parent):
    QObject(parent),
    location(location),
    normal(normal)
{

}

QVector3D *Vertex::getLocation() const
{
    return location;
}

QVector3D *Vertex::getNormal() const
{
    return normal;
}

QDebug operator<<(QDebug stream, const Vertex &vertex)
{
    stream << "Vertex ["
           << "\t location: "   << vertex.location
           << "\t normal: "     << vertex.normal
           << "]"               << &endl;
    return stream;
}


