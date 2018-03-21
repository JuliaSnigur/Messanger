include( ../../common.pri )

QT -= gui
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    dbtests.cpp


LIBS += $${GOOGLETESTSLIB_LIBRARY}
INCLUDEPATH += $${GOOGLETESTSLIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}
