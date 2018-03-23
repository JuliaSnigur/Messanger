include( ../../common.pri )


QT       -= gui
QT += network core sql

TARGET = SecureServerLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    SslServer.cpp \
    mythread.cpp

HEADERS += \
    stable.h \
    stdafx.h \
    SslServer.h \
    mythread.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += $${PARSEDATALIB_LIBRARY}
INCLUDEPATH += $${PARSEDATALIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH += $${DBLIB_INCLUDEPATH}

CONFIG += ordered

SecureServerLib.depends = DBLib ParseDataLib

CONFIG -= precompile_header
PRECOMPILED_HEADER = stable.h
