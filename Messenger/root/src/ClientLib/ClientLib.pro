include( ../../common.pri )
include( ../../lib.pri )
include( ../../root.pri )

QT       += core gui network widgets

########################################
<<<<<<< HEAD
CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h
=======
<<<<<<< HEAD
#PRECOMPILED_HEADER = stdafx.h
#CONFIG += precompile_header
=======
CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h
>>>>>>> master
>>>>>>> julia1
########################################

TARGET = ClientLib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += CLIENTLIB_LIBRARY

HEADERS += \
    clientlib.h \
    stdafx.h\
    stable.h\
<<<<<<< HEAD
=======
    structuser.h
>>>>>>> julia1

SOURCES += \
    clientlib.cpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    QMAKE_TARGET_PRODUCT = My Lib
    QMAKE_TARGET_DESCRIPTION = It is my library
}


