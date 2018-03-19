TEMPLATE = aux

#win32: PYTHON=python.exe
#else:  PYTHON=python
#system($$PYTHON qwe.py)

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
    src/GuiLib \
    src/SecureClientLib \
    src/SecureServerLib \
    src/Client \
    src/Server \
    src/GoogleTestsLib \
    src/GoogleTests


Client.depends =  SecureClientLib GuiLib
Server.depends =  SecureServerLib DBLib


SecureClientLib.depends = DBLib ParseDataLib
SecureServerLib.depends = DBLib ParseDataLib

SecureClientLib.depends=DBLib
SecureServerLib.depends=DBLib


