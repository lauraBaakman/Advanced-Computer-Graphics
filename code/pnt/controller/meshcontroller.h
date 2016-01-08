#ifndef MESHCONTROLLER_H
#define MESHCONTROLLER_H

#include <QObject>
#include "model/mesh.h"

class MeshController : public QObject
{
    Q_OBJECT
public:
    explicit MeshController(Mesh *mesh, QObject *parent = 0);

signals:

public slots:

private:
    Mesh *mesh;
};

#endif // MESHCONTROLLER_H
