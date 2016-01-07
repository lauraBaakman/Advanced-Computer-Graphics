#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T21:25:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pnt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/mesh.cpp \
    model/vertex.cpp \
    model/edge.cpp \
    settings.cpp \
    view/canvas.cpp

HEADERS  += mainwindow.h \
    main.ih \
    model/mesh.h \
    model/vertex.h \
    model/edge.h \
    settings.h \
    view/canvas.h

FORMS    += mainwindow.ui

DISTFILES +=
