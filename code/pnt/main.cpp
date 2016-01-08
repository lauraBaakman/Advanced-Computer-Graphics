#include <QApplication>

#include "main.ih"
#include "view/ui/mainwindow.h"

//Temp
#include <QFile>
#include "model/obj.h"
#include "model/mesh.h"


int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    setOpenGLVersion(majorOpenGLVersion, minorOpenGLVersion);

    //    MainWindow w;
    //    w.show();

    //    return a.exec();
    QFile file(":/models/resources/models/cube.obj");
    Obj* obj = Obj::fromFile(&file);
    Mesh mesh(obj);
}

void setOpenGLVersion(int const majorVersion, int const minorVersion)
{
    QSurfaceFormat glFormat;
    glFormat.setProfile(QSurfaceFormat::CoreProfile);

    glFormat.setVersion(majorVersion, minorVersion);
    glFormat.setOption(QSurfaceFormat::DebugContext);

    QSurfaceFormat::setDefaultFormat(glFormat);
}
