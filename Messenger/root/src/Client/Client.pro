include( ../../common.pri )
include( ../../app.pri )
include(../../root.pri)

QT       += core  quick core gui network qml

TARGET= Client
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
        main.cpp \

HEADERS += \
    stdafx.h
##############################





LIBS +=  $${CLIENTLIB_LIBRARY}
INCLUDEPATH+= $${CLIENTLIB_INCLUDEPATH}


LIBS +=  $${GUILIB_LIBRARY}
INCLUDEPATH+= $${GUILIB_INCLUDEPATH}

PRECOMPILED_HEADER = stdafx.h
CONFIG += precompile_header
###################################


