#include "obj.h"

const QString Obj::ObjLineTypes::vertex = "v";
const QString Obj::ObjLineTypes::face = "f";
const QString Obj::ObjLineTypes::vertexNormal = "vn";

const QRegExp Obj::floatRegularExpression("[-+]?[0-9]*\\.?[0-9]+");

Obj::Obj()
{

}

Obj* Obj::fromFile(QFile *file)
{
    qDebug() << "Received file: " << file->fileName();
    QTextStream* inStream = openFile(file);
    if(inStream) {
        Obj* obj = processFile(inStream);
        file->close();
        delete inStream;
        return obj;
    }
    return nullptr;
}

void Obj::add(Obj::VertexPosition *vertexPosition)
{
    vertexPositions.append(vertexPosition);
}

QTextStream* Obj::openFile(QFile *file)
{
    if(!(file->open(QIODevice::ReadOnly))){
        QMessageBox::critical(0, "Error", "The file " + file->fileName() + " could not be opened.\n\n" + file->errorString());
        return nullptr;
    }
    return new QTextStream(file);
}

Obj* Obj::processFile(QTextStream *stream)
{
    Obj* obj = new Obj();
    QString line;
    while(!stream->atEnd()){
        line = stream->readLine();
        obj = processLine(line, obj);
    }
    return obj;
}

Obj *Obj::processLine(QString line, Obj *obj)
{
    if(line.isEmpty()) return obj;

    Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;

    if (line.startsWith(Obj::ObjLineTypes::vertexNormal, caseSensitivity)){
        qDebug("Detected a vertex normal");
    } else if(line.startsWith(Obj::ObjLineTypes::vertex, caseSensitivity)){
        obj->add(VertexPosition::fromString(line));
    } else if (line.startsWith(Obj::ObjLineTypes::face, caseSensitivity)){
        qDebug("Detected a face");
    } //else ignore the line
    return obj;
}

QDebug operator<<(QDebug stream, const Obj &obj) {
    stream << "Obj[ "
           << "vertexPositions: ["    << obj.vertexPositions
           << "]"
           << &endl;
    return stream;
}

Obj::VertexPosition::VertexPosition(double x, double y, double z):
    QVector3D(x, y, z)
{}

Obj::VertexPosition* Obj::VertexPosition::fromString(QString string)
{


    QList<QString> numbers = extractMatchesFromString(string, floatRegularExpression);

    VertexPosition* position = new VertexPosition(
                numbers.at(0).toDouble(),
                numbers.at(1).toDouble(),
                numbers.at(2).toDouble());
    return position;
}



QList<QString> extractMatchesFromString(QString string, QRegExp regularExpression)
{
    QList<QString> matches;
    int floatPosition = 0;

    while((floatPosition = regularExpression.indexIn(string, floatPosition)) != -1){
        QString match = regularExpression.cap(0);
        matches.append(match);
        floatPosition += regularExpression.matchedLength();
    }
    return matches;
}
