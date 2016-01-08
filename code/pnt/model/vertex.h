#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include <QDebug>
#include <QVector3D>

class Vertex : public QObject
{
    Q_OBJECT
public:
    explicit Vertex(QVector3D location, QVector3D normal, QObject *parent = 0);

    QVector3D getLocation() const;

    static Vertex* fromObjString(QString string);

    friend QDebug operator<<(QDebug stream, const Vertex &vertex);

    QVector3D getNormal() const;

private:
    QVector3D location;
    QVector3D normal;

signals:

public slots:
};

#endif // VERTEX_H
