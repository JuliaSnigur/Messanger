
#win32: PYTHON_EXE=\src\Python27\python.exe
#else:  PYTHON_EXE=\src\Python27\python
#system(qwe.py)

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}
win32{
    CONFIG(debug, debug|release){
        QMAKE_POST_LINK = \"$${PYTHON_EXE}\" \"$${SRC}/PreBuild.py\" \"$${SRC}\" \"$${EXTERNALS}\" \"debug\"
    }
    else{
        QMAKE_POST_LINK = \"$${PYTHON_EXE}\" \"src/include/$${BUILD_FLAG}/qwe.py\" \"$${SRC}\" \"$${EXTERNALS}\"
    }
}
# вариант 1
#QMAKE_POST_LINK += $$quote(src\Python27\python.exe src/include/$${BUILD_FLAG}/qwe.py)
# вариант 2
QMAKE_POST_LINK += execfile('src/include/$${BUILD_FLAG}/qwe.py')
#CONFIG  += no_link target_predeps

#TEMPLATE = aux
#system(src\Python27\python.exe src/include/$${BUILD_FLAG}/qwe.py)
#TARGET   =
#system(src\Python27\python.exe src/include/$${BUILD_FLAG}/qwe.py)

#QMAKE_POST_LINK  += qwe.py
#QMAKE_CLEAN     += batch_output.obj
#CONFIG(python.exe qwe.py)
#QMAKE_POST_LINK += system(src\Python27\python.exe(qwe.py)
#$$QMAKE_COPY

#win32 {
#    PWD_WIN = $${PWD}
#   PWD_WIN ~= s,/,\\,g
#
#    QMAKE_POST_LINK += $$quote(mkdir DestFolder)
#    QMAKE_POST_LINK += $$quote(xcopy $${PWD_WIN}\\TestData $${OUT_PWD_WIN}\\TestData /E)
#    QMAKE_CLEAN += /s /f /q TestData && rd /s /q TestData
#}#
#
#unix {
#    QMAKE_POST_LINK += $$quote(cp -rf $${PWD}/TestData $${OUT_PWD})
#    QMAKE_CLEAN += -r TestData
#}

DISTFILES += \
    root.pri\
    common.pri\
    app.pri\
    lib.pri




TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS  = \
    src/DBLib \
    src/ParseDataLib \
    #src/ServerLib \
    #src/ClientLib \
    src/GuiLib \
    src/SecureClientLib \
    src/SecureServerLib \
    src/Client \
    src/Server \
    #src/Include

Client.depends =  SecureClientLib ParseDataLib
Server.depends =  SecureServerLib DBLib ParseDataLib

SecureClientLib.depends=DBLib
SecureServerLib.depends=DBLib


