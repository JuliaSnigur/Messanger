include( ../../common.pri )


DESTDIR = $${BIN_PATH}/
linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/


QT       += core network widgets sql
CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS +=

SOURCES += main.cpp

LIBS+=$${PARSEDATALIB_LIBRARY}
INCLUDEPATH+=$${PARSEDATALIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}


LIBS +=  $${SECURESERVERLIB_LIBRARY}
INCLUDEPATH+= $${SECURESERVERLIB_INCLUDEPATH}


CONFIG += ordered
Server.depends = DBLib SecureServerLib ParseDataLib
