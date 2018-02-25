include(../../common.pri)
include( ../../lib.pri )
include(../../root.pri)


QT += quick core gui network
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp \
    signin.cpp

HEADERS += \
    stdafx.h \
    signin.h


DISTFILES += \
    main.qml\
    MyButton.qml \
    Registration.qml \
    Authorization.qml

######################
TARGET = GuiLib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += GUILIB_LIBRARY

LIBS +=  $${CLIENTLIB_LIBRARY}
INCLUDEPATH+= $${CLIENTLIB_INCLUDEPATH}

PRECOMPILED_HEADER = stdafx.h
CONFIG += precompile_header
###################

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    QMAKE_TARGET_PRODUCT = My Lib
    QMAKE_TARGET_DESCRIPTION = It is my library
}
