include( ../../common.pri )

DESTDIR = $${LIBS_PATH}/
win32: DLLDESTDIR = $${BIN_PATH}/
#VERSION = 1.0.0
QMAKE_TARGET_COPYRIGHT = (c) My Company Name

QT       -= gui

TARGET = GTLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/gtest.cc \
    src/gtest_main.cc \
    src/gtest-all.cc \
    src/gtest-death-test.cc \
    src/gtest-filepath.cc \
    src/gtest-port.cc \
    src/gtest-printers.cc \
    src/gtest-test-part.cc \
    src/gtest-typed-test.cc

HEADERS += \
    src/gtest-internal-inl.h \
    gtest/gtest.h \
    gtest/gtest_pred_impl.h \
    gtest/gtest_prod.h \
    gtest/gtest-death-test.h \
    gtest/gtest-message.h \
    gtest/gtest-param-test.h \
    gtest/gtest-param-test.h.pump \
    gtest/gtest-printers.h \
    gtest/gtest-spi.h \
    gtest/gtest-test-part.h \
    gtest/gtest-typed-test.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
