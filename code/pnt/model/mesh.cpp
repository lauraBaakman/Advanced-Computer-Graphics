#include "mesh.h"

Mesh::Mesh(QObject *parent):
    QObject(parent)
{
}

//Mesh* Mesh::fromObjFile(QString filename)
//{
//    QFile file(filename);
//    if (file.open(QIODevice::ReadOnly)){
//        QTextStream in(&file);
//        QString line;
//        while (!in.atEnd()){
//            line = in.readLine();
//        }
//        file.close();
//    } else {
//        QMessageBox::critical(0, "Error", "The file " + file.fileName() + " could not be opened.\n\n" + file.errorString());
//    }
//    return nullptr;
//}
