TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
QT += core

SOURCES += main.cpp \
    file/file-reader.cpp \
    structures/instance.cpp \
    structures/geom-node.cpp \
    structures/plane.cpp \
    worker.cpp \
    nearestneighbour.cpp

HEADERS += \
    file/file-reader.h \
    structures/instance.h \
    structures/geom-node.h \
    structures/plane.h \
    worker.h \
    timer.h \
    nearestneighbour.h
