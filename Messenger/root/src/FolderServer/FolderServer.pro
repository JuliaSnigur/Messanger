TEMPLATE = aux

#win32: PYTHON=python.exe
#else:  PYTHON=python
#system($$PYTHON qwe.py)

DISTFILES += \
    common.pri\

RESOURCES += \
    secure/client.crt \
    secure/client.key \
    secure/sslserver.pem \
    secure/sslserver.key

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS  = \
        $${INC_PATH}DBLib \
        $${INC_PATH}ParseDataLib \
        $${INC_PATH}SecureServerLib \
        $${INC_PATH}Server

Server.depends =  SecureServerLib DBLib ParseDataLib
SecureServerLib.depends = DBLib ParseDataLib



