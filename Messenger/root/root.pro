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
    src/ParseDataLib \
    src/GuiLib \
    src/SecureClientLib \
    src/SecureServerLib \
    src/Client \
    src/Server \
    src/GTLib \
    src/GTests


Client.depends =  SecureClientLib GuiLib ParseDataLib
Server.depends =  SecureServerLib DBLib ParseDataLib

SecureClientLib.depends = DBLib ParseDataLib
SecureServerLib.depends = DBLib ParseDataLib



