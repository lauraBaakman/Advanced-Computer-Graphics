#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>

#include "vertex.h"

class Mesh : public QObject
{
    Q_OBJECT
public:
    explicit Mesh(QObject *parent = 0);

    static Mesh* fromObjFile(QString file);

private:
    QVector<Vertex*> vertices;


signals:

public slots:
};

#endif // MESH_H
