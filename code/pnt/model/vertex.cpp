#include "vertex.h"

Vertex::Vertex(QVector3D location, QObject *parent) :
    QObject(parent),
    location(location)
{

}

QVector3D Vertex::getLocation() const
{
    return location;
}

QVector3D Vertex::getNormal() const
{
    return normal;
}

void Vertex::setNormal(const QVector3D &value)
{
    normal = value;
}

Vertex *Vertex::fromObjString(QString string)
{

}

QDebug operator<<(QDebug stream, const Vertex &vertex)
{
    stream << "Vertex ["
           << "\t location: "   << vertex.location  << &endl
           << "\t normal: "     << vertex.normal    << &endl
           << "]"                                   << &endl;
}


