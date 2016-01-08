#ifndef EDGE_H
#define EDGE_H

#include <QObject>

#include "vertex.h"

class Edge : public QObject
{
    Q_OBJECT
public:
    explicit Edge(Vertex* a, Vertex* b, QObject *parent = 0);

    friend QDebug operator<<(QDebug stream, const Edge &edge);

private:
    Vertex* a;
    Vertex* b;

signals:

public slots:
};

#endif // EDGE_H
