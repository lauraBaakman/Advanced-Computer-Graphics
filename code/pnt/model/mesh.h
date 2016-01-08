#ifndef MESH_H
#define MESH_H

#include <QObject>

#include <QVector>

#include "vertex.h"
#include "edge.h"
#include "obj.h"

class Mesh : public QObject
{
    Q_OBJECT
public:
    explicit Mesh(Obj *object, QObject *parent = 0);

    friend QDebug operator<<(QDebug stream, const Mesh &mesh);
private:
    QList<unsigned int> faces;
    QVector<QVector3D> vertexPositions;
    QVector<QVector3D> vertexNormals;

    void addVertices(Obj *object);

signals:

public slots:
};

#endif // MESH_H
