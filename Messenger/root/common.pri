#фиксируется путь к корневому каталогу проекта, относительно
#которого будем определять все остальные пути
PROJECT_ROOT_PATH = $${PWD}/

#Определяем  под какой ОС происходит сборка
win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

#Определяется значение BUILD_FLAG, которое будет указывать на версию
#используемого подкаталога в bin/ и build/:
CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

LIBS_PATH = $${PROJECT_ROOT_PATH}/lib.$${OS_SUFFIX}/$${BUILD_FLAG}/
INC_PATH = $${PROJECT_ROOT_PATH}/src
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/


#Ниже стоит блок, который задает пути сборки для файлов ресурсов rcc,
#файлов графического интерфейса ui,
#МОК-файлов moc и объектных файлов obj
BUILD_PATH = $${PROJECT_ROOT_PATH}/obj/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

LIBS += -L$${LIBS_PATH}/

INCLUDEPATH += $${INC_PATH}/
INCLUDEPATH += $${IMPORT_PATH}/

linux-g++: QMAKE_CXXFLAGS += -std=c++11
##################################################
# указывает путь, в который будет помещен готовый исполняемый файл
DESTDIR = $${BIN_PATH}/
linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/
################################################
DESTDIR = $${LIBS_PATH}/
win32: DLLDESTDIR = $${BIN_PATH}/
#VERSION = 1.0.0
QMAKE_TARGET_COPYRIGHT = (c) My Company Name
###################################################


###################################################

CLIENTLIB_INCLUDEPATH= $${INC_PATH}/ClientLib
CLIENTLIB_LIBRARY = -lClientLib$${LIB_SUFFIX}

GUILIB_INCLUDEPATH= $${INC_PATH}/GuiLib
GUILIB_LIBRARY = -lGuiLib$${LIB_SUFFIX}

DBLIB_INCLUDEPATH= $${INC_PATH}/DBLib
DBLIB_LIBRARY = -lDBLib$${LIB_SUFFIX}

SERVERLIB_INCLUDEPATH= $${INC_PATH}/ServerLib
SERVERLIB_LIBRARY = -lServerLib$${LIB_SUFFIX}

PARSEDATALIB_INCLUDEPATH= $${INC_PATH}/DataLib
PARSEDATALIB_LIBRARY = -lDataLib$${LIB_SUFFIX}

SECURESERVERLIB_LIBRARY=-lSecureServerLib$${LIB_SUFFIX}
SECURESERVERLIB_INCLUDEPATH=$${INC_PATH}/SecureServerLib

SECURECLIENTLIB_LIBRARY=-lSecureClientLib$${LIB_SUFFIX}
SECURECLIENTLIB_INCLUDEPATH=$${INC_PATH}/SecureClientLib

GOOGLETESTSLIB_LIBRARY=-lGTLib$${LIB_SUFFIX}
GOOGLETESTSLIB_INCLUDEPATH=$${INC_PATH}/GTLib


#CONFIG += precompile_header
#PRECOMPILED_HEADER = stable.h



