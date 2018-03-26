include( ../../common.pri )


DESTDIR = $${BIN_PATH}/
linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/


QT       += core network qml sql

CONFIG += c++11  #console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    client.cpp

HEADERS += \
    client.h 

CONFIG += ordered

LIBS+=$${PARSEDATALIB_LIBRARY}
INCLUDEPATH+=$${PARSEDATALIB_INCLUDEPATH}

LIBS +=  $${DBLIB_LIBRARY}
INCLUDEPATH+= $${DBLIB_INCLUDEPATH}

LIBS +=  $${GUILIB_LIBRARY}
INCLUDEPATH+= $${GUILIB_INCLUDEPATH}

LIBS+=$${SECURECLIENTLIB_LIBRARY}
INCLUDEPATH+=$${SECURECLIENTLIB_INCLUDEPATH}

Client.depends = DataLib DBLib GuiLib SecureClientLib



