#include "obj.h"

const QString Obj::ObjLineTypes::vertex = "v";
const QString Obj::ObjLineTypes::face = "f";
const QString Obj::ObjLineTypes::vertexNormal = "vn";

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

    //Brrr, should be strings with descriptive names
    if (line.startsWith(Obj::ObjLineTypes::vertexNormal, caseSensitivity)){
        qDebug("Detected a vertex normal");
    } else if(line.startsWith(Obj::ObjLineTypes::vertex, caseSensitivity)){
        VertexPosition *position = VertexPosition::fromString(line);
    } else if (line.startsWith(Obj::ObjLineTypes::face, caseSensitivity)){
        qDebug("Detected a face");
    } //else ignore the line
    return obj;
}

Obj::VertexPosition::VertexPosition(){}

Obj::VertexPosition* Obj::VertexPosition::fromString(QString string)
{
    VertexPosition *position = new VertexPosition();

   qDebug() << "Todo: convertet string to VertexPosition";

    return position;
}
