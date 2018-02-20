include(common.pri)

SERVERLIB_INCLUDEPATH= $${INC_PATH}/ServerLib
SERVERLIB_LIBRARY = -lServerLib$${LIB_SUFFIX}

#unix:   LIBS += -lServerLib$${LIB_SUFFIX}
#win32:  LIBS += $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/ServerLib/obj/serverlib.o

#INCLUDEPATH+=$${INC_PATH}/ServerLib
