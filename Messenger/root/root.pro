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
    src/DBLib \
    src/DataLib \
    src/GuiLib \
    src/SecureClientLib \
    src/SecureServerLib \
    src/Client \
    src/Server \
    src/GTLib \
    src/GTests\

Client.depends = GuiLib SecureClientLib  DataLib
Server.depends = SecureServerLib DBLib DataLib

SecureClientLib.depends = DBLib DataLib
SecureServerLib.depends = DBLib DataLib



