TEMPLATE = app
TARGET = rfirst_csecond
CONFIG -= console
#CONFIG -= app_bundle
#CONFIG -= qt
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    file/file-reader.cpp \
    structures/instance.cpp \
    structures/geom-node.cpp \
    structures/plane.cpp \
    worker.cpp \
    nearestneighbour.cpp \
    window/mainwindow.cpp

HEADERS += \
    file/file-reader.h \
    structures/instance.h \
    structures/geom-node.h \
    structures/plane.h \
    worker.h \
    timer.h \
    nearestneighbour.h \
    window/mainwindow.h

FORMS += \
    window/mainwindow.ui
