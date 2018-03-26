include( ../../common.pri )

DESTDIR = $${LIBS_PATH}/
win32: DLLDESTDIR = $${BIN_PATH}/
QMAKE_TARGET_COPYRIGHT = (c) My Company Name


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
