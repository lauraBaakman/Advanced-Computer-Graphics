#include "obj.h"

const QString Obj::ObjLineTypes::vertex = "v";
const QString Obj::ObjLineTypes::face = "f";
const QString Obj::ObjLineTypes::vertexNormal = "vn";

const QRegExp Obj::floatRegularExpression("[-+]?[0-9]*\\.?[0-9]+");

Obj::Obj()
{
    counters.faces = 0;
    counters.vertexNormals = 0;
    counters.vertexPositions = 0;
}

Obj::~Obj()
{
    qDebug() << "Obj destructor";
    for(int i = 0; i < vertexPositions.size(); i++){
        delete vertexPositions[i];
    }
    for(int i = 0; i < vertexNormals.size(); i++){
        delete vertexNormals[i];
    }
    for(int i = 0; i < faces.size(); i++){
        delete faces[i];
    }
}

Obj* Obj::fromFile(QFile *file)
{
    QTextStream* inStream = openFile(file);
    if(inStream) {
        Obj* obj = processFile(inStream);
        file->close();
        delete inStream;
        return obj;
    }
    return nullptr;
}

QMap<unsigned int, Obj::VertexPosition *> Obj::getVertexPositions() const
{
    return vertexPositions;
}

QMap<unsigned int, Obj::VertexNormal *> Obj::getVertexNormals() const
{
    return vertexNormals;
}

QMap<unsigned int, Obj::Face *> Obj::getFaces() const
{
    return faces;
}

void Obj::add(Obj::VertexPosition *vertexPosition)
{
    vertexPositions.insert(counters.vertexPositions++, vertexPosition);
}

void Obj::add(Obj::VertexNormal *vertexNormal)
{
    vertexNormals.insert(counters.vertexNormals++, vertexNormal);
}

void Obj::add(Obj::Face *face)
{
    faces.insert(counters.faces++, face);
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
        obj->add(VertexNormal::fromString(line));
    } else if(line.startsWith(Obj::ObjLineTypes::vertex, caseSensitivity)){
        obj->add(VertexPosition::fromString(line));
    } else if (line.startsWith(Obj::ObjLineTypes::face, caseSensitivity)){
        obj->add(Face::fromString(line));
    } //else ignore the line
    return obj;
}

QDebug operator<<(QDebug stream, const Obj &obj) {
    stream << "Obj" <<  &endl;
    stream << "vertexPositions: " << &endl << "\t ";
    for(auto i : obj.vertexPositions){
        stream << *i;
    }
    stream << &endl;

    stream << "vertexNormals: " << &endl << "\t ";
    for(auto i : obj.vertexNormals){
        stream << *i;
    }
    stream << &endl;

    stream << "faces: " << &endl << "\t ";
    for(auto i : obj.faces){
        stream << *i;
    }
    stream << &endl;

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

Obj::VertexNormal::VertexNormal(double x, double y, double z):
    QVector3D(x, y, z)
{}

Obj::VertexNormal *Obj::VertexNormal::fromString(QString string)
{
    QList<QString> numbers = extractMatchesFromString(string, floatRegularExpression);
    VertexNormal* normal = new VertexNormal(
                numbers.at(0).toDouble(),
                numbers.at(1).toDouble(),
                numbers.at(2).toDouble());
    return normal;
}

Obj::Face::Face()
{}

Obj::Face *Obj::Face::fromString(QString string)
{
    Face *face = new Face();
    QRegExp regEx("([1-9][0-9]*)//[1-9][0-9]*");
    QList<QList<QString>> numbers = extractMatchesFromString(string, regEx, 1);
    for(auto number : numbers){
        face->append(number.first().toInt() - 1);
    }
    return face;
}

QList<QString> extractMatchesFromString(QString string, QRegExp regEx)
{
    QList<QString> matches;
    int floatPosition = 0;

    while((floatPosition = regEx.indexIn(string, floatPosition)) != -1){
        QString match = regEx.cap(0);
        matches.append(match);
        floatPosition += regEx.matchedLength();
    }
    return matches;
}

QList<QList<QString>> extractMatchesFromString(QString string, QRegExp regEx, int numGroups){
    QList<QList<QString>> matches;
    int floatPosition = 0;
    while((floatPosition = regEx.indexIn(string, floatPosition)) != -1){
        QString match;
        QList<QString> groups;
        for(int i = 1; i <= numGroups; i++){
            match = regEx.cap(i);
            groups.append(match);
        }
        matches.append(groups);
        floatPosition += regEx.matchedLength();
    }
    return matches;
}
