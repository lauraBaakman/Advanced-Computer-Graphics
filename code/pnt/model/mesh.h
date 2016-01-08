#ifndef MESH_H
#define MESH_H

#include <QObject>

#include <QVector>

#include "vertex.h"
#include "edge.h"

class Mesh : public QObject
{
    Q_OBJECT
public:
    explicit Mesh(QObject *parent = 0);

private:

    QVector<Vertex*> vertices;
    QVector<Edge*> edges;
    QVector<QVector3D> vertexPositions;
    QVector<QVector3D> vertexNormals;

signals:

public slots:
};

#endif // MESH_H
