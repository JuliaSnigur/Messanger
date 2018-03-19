#include( ../../common.pri )
#include( ../../app.pri )
include(../../root.pri)

#include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG += thread
CONFIG -= qt

#HEADERS +=     tst_dbtestscreate.h

SOURCES +=     main.cpp \
    test.cpp


LIBS +=  $${GOOGLETESTSLIB_LIBRARY}

LIBS += "D:\Project\SecureMessanger\Messenger\root\lib.win32\debug"

INCLUDEPATH+= "D:\Project\SecureMessanger\Messenger\root\src\GoogleTestsLib" #$${GOOGLETESTSLIB_INCLUDEPATH}
