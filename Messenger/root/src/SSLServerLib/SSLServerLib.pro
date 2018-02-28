include( ../../common.pri )
include( ../../lib.pri )
include( ../../root.pri )

QT       += core network widgets
QT       -= gui

CONFIG += c++11 static

TARGET = SSLServerLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

PRECOMPILED_HEADER =stable.h
CONFIG -= precompile_header

HEADERS += $$files($${PWD}/*.h)

SOURCES += $$files($${PWD}/*.cpp) \

unix {
    target.path = /usr/lib
    INSTALLS += target
}



#INCLUDEPATH+= $${INC_PATH}/openssl/include
#LIBS += $${INC_PATH}/openssl/-llibcrypto
#LIBS += $${INC_PATH}/openssl/-llibssl

#win32 {
#    QMAKE_TARGET_PRODUCT = My Lib
#    QMAKE_TARGET_DESCRIPTION = It is my library
#}
