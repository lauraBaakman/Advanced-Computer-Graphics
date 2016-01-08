#ifndef OBJ_H
#define OBJ_H

#include <QObject>
#include <QFile>
#include <QVector3D>
#include <QTextStream>
#include <QMessageBox>

#include <QDebug>

class Obj
{
public:
    Obj();

    static Obj* fromFile(QFile *file);

private:
    class VertexPosition;
//    class vertexNormal;
//    class face;

    QList<Obj::VertexPosition*> vertexPositions;

    static QTextStream* openFile(QFile *file);
    static Obj* processFile(QTextStream* stream);
    static Obj* processLine(QString line, Obj *obj);

    static const struct ObjLineTypes {
       static const QString vertex;
       static const QString vertexNormal;
       static const QString face;
     } objLineTypes;

};

class Obj::VertexPosition : public QVector3D {
public:
    VertexPosition();

    static Obj::VertexPosition* fromString(QString string);
};

#endif // OBJ_H
