TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
QT += core

SOURCES += main.cpp \
    file/file-reader.cpp \
    structures/symmetrical-instance.cpp \
    structures/geom-node.cpp

HEADERS += \
    file/file-reader.h \
    structures/symmetrical-instance.h \
    structures/geom-node.h

