include( ../../common.pri )
include( ../../lib.pri )
include( ../../root.pri )

QT      -= gui
QT      += core widgets network

CONFIG+=c++11 static

TARGET = SSLClientLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

PRECOMPILED_HEADER =stable.h
CONFIG -= precompile_header

SOURCES += $$files($${PWD}/*.cpp)

HEADERS += $$files($${PWD}/*.h)\
           #openssl/$$files($${PWD}/*.h)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH+= $${INC_PATH}/openssl/include
LIBS += $${INC_PATH}/openssl/-llibcrypto
LIBS += $${INC_PATH}/openssl/-llibssl

#win32 {
#    QMAKE_TARGET_PRODUCT = My Lib
#    QMAKE_TARGET_DESCRIPTION = It is my library
#}
