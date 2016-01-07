#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T21:25:10
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pnt
TEMPLATE = app


SOURCES += main.cpp\
    view/ui/mainwindow.cpp \
    model/mesh.cpp \
    model/vertex.cpp \
    model/edge.cpp \
    settings/settings.cpp \
    view/canvas.cpp \
    view/ui/sidebar.cpp \
    controller/meshcontroller.cpp \
    settings/render.cpp

HEADERS  += view/ui/mainwindow.h \
    main.ih \
    model/mesh.h \
    model/vertex.h \
    model/edge.h \
    settings/settings.h \
    view/canvas.h \
    view/ui/sidebar.h \
    controller/meshcontroller.h \
    settings/render.h

FORMS    += view/ui/mainwindow.ui \
    view/ui/sidebar.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
