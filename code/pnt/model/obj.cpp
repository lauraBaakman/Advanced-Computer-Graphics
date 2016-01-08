#include "obj.h"

Obj::Obj(QFile *file)
{
    qDebug() << "Received file: " << file->fileName();

    openFile(file);

    //openFile

    //processFile

    //closeFile
    //delete textstream
}

QTextStream* Obj::openFile(QFile *file) const
{
    if(!(file->open(QIODevice::ReadOnly))){
        QMessageBox::critical(0, "Error", "The file " + file->fileName() + " could not be opened.\n\n" + file->errorString());
        return nullptr;
    }
    return new QTextStream(file);
}
