include( ../../common.pri )

DESTDIR = $${BIN_PATH}/
linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/


QT -= gui
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    dbservertests.cpp \
    dbclienttests.cpp \
    requesttests.cpp


LIBS += $${GOOGLETESTSLIB_LIBRARY}
INCLUDEPATH += $${GOOGLETESTSLIB_INCLUDEPATH}

LIBS+=$${PARSEDATALIB_LIBRARY}
INCLUDEPATH+=$${PARSEDATALIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}

