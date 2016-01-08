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
    Obj(QFile *file);

private:

    QTextStream* openFile(QFile *file) const;

//    class vertexPosition;
//    class vertexNormal;
//    class face;


//    QList<vertexPosition*> vertexPositions;
};

//class Obj::vertexPosition : public QVector3D {
//public:
//    static fromString(QString string);
//};

#endif // OBJ_H
