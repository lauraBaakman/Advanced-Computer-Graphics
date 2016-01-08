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
    stream << "Obj[ "                                             <<  &endl
           << "  vertexPositions:   ["  << obj.vertexPositions    <<  &endl
           << "  vertexNormals:     ["  << obj.vertexNormals      <<  &endl
           << "  faces:             ["  << obj.faces              <<  &endl
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
    QRegExp regEx("[1-9][0-9]*//[1-9][0-9]*");
    QList<QString> edgeStrings = extractMatchesFromString(string, regEx);
    Edge* edge;
    for(auto edgeString : edgeStrings){
        edge = Edge::fromString(edgeString);
        qDebug() << *edge;
    }
    return nullptr;
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

Obj::Edge::Edge(int a, int b):
    QPair<unsigned int, unsigned int>(a, b)
{}

Obj::Edge *Obj::Edge::fromString(QString string)
{
    QRegExp regEx("[1-9][0-9]*");
    QList<QString> numbers = extractMatchesFromString(string, regEx);
    Edge *edge = new Edge(
                numbers.at(0).toInt(),
                numbers.at(1).toInt());
    return edge;
}
