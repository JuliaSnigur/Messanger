include( ../../common.pri )

QT       += core network widgets sql
CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += stable.h \
           stdafx.h

SOURCES += main.cpp

PRECOMPILED_HEADER = stable.h
CONFIG -= precompile_header

LIBS+=$${PARSEDATALIB_LIBRARY}
INCLUDEPATH+=$${PARSEDATALIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}


LIBS +=  $${SECURESERVERLIB_LIBRARY}
INCLUDEPATH+= $${SECURESERVERLIB_INCLUDEPATH}


CONFIG += ordered
Server.depends = DBLib SecureServerLib ParseDataLib
