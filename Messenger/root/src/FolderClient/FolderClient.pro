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
    $${INC_PATH}GuiLib \
    $${INC_PATH}SecureClientLib \
    $${INC_PATH}Client \

Client.depends = GuiLib SecureClientLib  ParseDataLib

SecureClientLib.depends = DBLib ParseDataLib


