include( ../../common.pri )
include( ../../lib.pri )

QT       += core network
QT       -= gui

CONFIG += c++11

TARGET = SSLServerLib$${LIB_SUFFIX}
TEMPLATE = lib
#TARGET = sslserverlib
#CONFIG   += console
CONFIG   -= app_bundle

#TEMPLATE = app

DEFINES += SSLSERVERLIB_LIBRARY

HEADERS += $$files($${PWD}/*.h)

SOURCES += $$files($${PWD}/*.cpp) \

#RESOURCES += securesocketclient.qrc


#target.path = $$[QT_INSTALL_EXAMPLES]/websockets/sslechoserver
#INSTALLS += target

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    QMAKE_TARGET_PRODUCT = My Lib
    QMAKE_TARGET_DESCRIPTION = It is my library
}
