include( ../../common.pri )
include( ../../lib.pri )
include( ../../root.pri )


QT       -= gui

TARGET = GoogleTestsLib$${LIB_SUFFIX}
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
    gmock.cc \
    gmock_main.cc \
    gmock-all.cc \
    gmock-cardinalities.cc \
    gmock-internal-utils.cc \
    gmock-matchers.cc \
    gmock-spec-builders.cc \
    gtest.cc \
    gtest_main.cc \
    gtest-all.cc \
    gtest-death-test.cc \
    gtest-filepath.cc \
    gtest-port.cc \
    gtest-printers.cc \
    gtest-test-part.cc \
    gtest-typed-test.cc

HEADERS += \
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
    gtest/gtest-typed-test.h \
    gmock/gmock.h \
    gmock/gmock-actions.h \
    gmock/gmock-cardinalities.h \
    gmock/gmock-generated-actions.h \
    gmock/gmock-generated-actions.h.pump \
    gmock/gmock-generated-function-mockers.h \
    gmock/gmock-generated-function-mockers.h.pump \
    gmock/gmock-generated-matchers.h \
    gmock/gmock-generated-matchers.h.pump \
    gmock/gmock-generated-nice-strict.h \
    gmock/gmock-matchers.h \
    gmock/gmock-more-actions.h \
    gmock/gmock-more-matchers.h \
    gmock/gmock-spec-builders.h \
    gtest-internal-inl.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    gmock/gmock-generated-nice-strict.h.pump

SUBDIRS += \
    GoogleTestsLib.pro
