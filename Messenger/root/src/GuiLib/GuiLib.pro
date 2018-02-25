<<<<<<< HEAD
include( ../../common.pri )
include( ../../app.pri )
include(../../root.pri)

QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    mywidget.cpp \
    signin.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =



HEADERS += \
    mywidget.h \
    signin.h \
    stdafx.h


PRECOMPILED_HEADER = stdafx.h
CONFIG += precompile_header
=======
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
>>>>>>> master
