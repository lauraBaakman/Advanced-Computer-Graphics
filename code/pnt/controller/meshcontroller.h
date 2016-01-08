#ifndef MESHCONTROLLER_H
#define MESHCONTROLLER_H

#include <QObject>
#include "model/mesh.h"
#include "model/obj.h"

class MeshController : public QObject
{
    Q_OBJECT
public:
    explicit MeshController(QObject *parent = 0);
    ~MeshController();
signals:

public slots:
    void onModelChanged(QString modelPath);

private:
    Mesh *mesh;
};

#endif // MESHCONTROLLER_H
