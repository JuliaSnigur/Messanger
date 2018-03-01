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

OPENSSL_PATH=$${PROJECT_ROOT_PATH}/../openssl/$${BUILD_FLAG}/


#Ниже стоит блок, который задает пути сборки для файлов ресурсов rcc,
#файлов графического интерфейса ui,
#МОК-файлов moc и объектных файлов obj
BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/


LIBS += -L$${LIBS_PATH}/
LIBS+=-L$${OPENSSL_PATH}/

INCLUDEPATH += $${INC_PATH}/

INCLUDEPATH += $${IMPORT_PATH}/

linux-g++: QMAKE_CXXFLAGS += -std=c++11
