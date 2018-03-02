include( ../../common.pri )
include( ../../lib.pri )
include( ../../root.pri )

QT      -= gui
QT      += core widgets network

TARGET = ServerLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

PRECOMPILED_HEADER =stable.h
CONFIG -= precompile_header

SOURCES += \
    MyServer.cpp
HEADERS += \
    MyServer.h \
    stable.h \
    stdafx.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}


LIBS+=$${PARSEDATALIB_LIBRARY}
INCLUDEPATH+=$${PARSEDATALIB_INCLUDEPATH}




#win32 {
#    QMAKE_TARGET_PRODUCT = My Lib
#    QMAKE_TARGET_DESCRIPTION = It is my library
#}
