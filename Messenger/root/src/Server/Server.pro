include( ../../common.pri )
include( ../../app.pri )
include(../../root.pri)

QT       += core network widgets

#CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += $$files($${PWD}/*.h)

SOURCES += $$files($${PWD}/*.cpp)

PRECOMPILED_HEADER = stable.h
CONFIG -= precompile_header

LIBS +=  $${SERVERLIB_LIBRARY}
message($${SERVERLIB_LIBRARY})
INCLUDEPATH+= $${SERVERLIB_INCLUDEPATH}

LIBS +=  $${SSLSERVERLIB_LIBRARY}
message($${SSLSERVERLIB_LIBRARY})
INCLUDEPATH+= $${SSLSERVERLIB_INCLUDEPATH}


#TEMPLATE     = app

#QT += gui network widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += c++11 console
#CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#HEADERS += $$files($${PWD}/*.h) \

#SOURCES += $$files($${PWD}/*.cpp) \

#LIBS +=  $${SERVERLIB_LIBRARY}
#INCLUDEPATH+= $${SERVERLIB_INCLUDEPATH}

#PRECOMPILED_HEADER = stdafxs.h
#CONFIG += precompile_header
##############################
#TARGET= Server


