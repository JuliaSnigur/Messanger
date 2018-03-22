include( ../../common.pri )

QT -= gui
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    dbservertests.cpp \
    dbclienttests.cpp


LIBS += $${GOOGLETESTSLIB_LIBRARY}
INCLUDEPATH += $${GOOGLETESTSLIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}

HEADERS += \
    stable.h \
    stdafx.h

CONFIG -= precompile_header
PRECOMPILED_HEADER = stable.h
