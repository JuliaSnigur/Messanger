include( ../../common.pri )
include( ../../lib.pri )
include( ../../root.pri )

QT      -= gui
QT      += core widgets network sql

TARGET = ServerLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

PRECOMPILED_HEADER =stable.h
CONFIG -= precompile_header

SOURCES += \
    ServerSocket.cpp
HEADERS += \
    stable.h \
    stdafx.h \
    ServerSocket.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}



LIBS+=$${PARSEDATALIB_LIBRARY}
INCLUDEPATH+=$${PARSEDATALIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}
