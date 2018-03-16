TEMPLATE = aux
system(qwe.py)
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
    #src/ServerLib \
    #src/ClientLib \
    src/GuiLib \
    src/SecureClientLib \
    src/SecureServerLib \
    src/Client \
    src/Server


Client.depends =  SecureClientLib GuiLib
Server.depends =  SecureServerLib DBLib

<<<<<<< HEAD
SecureClientLib.depends = DBLib ParseDataLib
SecureServerLib.depends = DBLib ParseDataLib
=======
SecureClientLib.depends=DBLib
SecureServerLib.depends=DBLib


>>>>>>> 2a1633cb0aa92d78593e0a08d4745493b34af37b
