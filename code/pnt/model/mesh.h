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
    explicit Mesh(QObject *parent = 0);
    ~Mesh();

    friend QDebug operator<<(QDebug stream, const Mesh &mesh);
private:
    QVector<QVector3D> vertexPositions;
    QVector<QVector3D> vertexNormals;

    QVector<unsigned int> indexBuffer;

    void addVertices(Obj *object);
    void createIndexBuffer(Obj* object);

signals:

public slots:
};

#endif // MESH_H
