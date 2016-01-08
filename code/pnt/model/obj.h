#ifndef OBJ_H
#define OBJ_H

#include <QObject>
#include <QFile>
#include <QVector3D>
#include <QTextStream>
#include <QMessageBox>
#include <QList>

#include <QDebug>

class Obj
{
public:
    Obj();

    static Obj* fromFile(QFile *file);

    friend QDebug operator<<(QDebug stream, const Obj &obj);

private:
    class VertexPosition;
    //    class vertexNormal;
    //    class face;

    QList<Obj::VertexPosition*> vertexPositions;

    void add(Obj::VertexPosition* vertexPosition);

    static QTextStream* openFile(QFile *file);
    static Obj* processFile(QTextStream* stream);
    static Obj* processLine(QString line, Obj *obj);

    static const struct ObjLineTypes {
        static const QString vertex;
        static const QString vertexNormal;
        static const QString face;
    } objline;

    static const QRegExp floatRegularExpression;

};

QList<QString> extractMatchesFromString(QString string, QRegExp regularExpression);

class Obj::VertexPosition : public QVector3D {
public:
    VertexPosition(double x, double y, double z);

    static Obj::VertexPosition* fromString(QString string);
};

#endif // OBJ_H
