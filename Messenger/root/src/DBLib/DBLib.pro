include( ../../common.pri )

DESTDIR = $${LIBS_PATH}/
win32: DLLDESTDIR = $${BIN_PATH}/
QMAKE_TARGET_COPYRIGHT = (c) My Company Name

QT       -= gui
QT      += sql

TARGET = DBLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    request.cpp \
    dbserverpresenter.cpp \
    dbclientpresenter.cpp \
    dbpresenter.cpp


HEADERS += \
    request.h \
    dbserverpresenter.h \
    dbclientpresenter.h \
    dbpresenter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += $${PARSEDATALIB_LIBRARY}
INCLUDEPATH += $${PARSEDATALIB_INCLUDEPATH}

DBLib.depends = DataLib
