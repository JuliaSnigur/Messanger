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
    #src/Client/client.pro \
    #src/Server/server.pro \
    #src/Client/Client/client.pro \
    #src/Server/Server/server.pro

Client.depends =  SecureClientLib GuiLib
Server.depends =  SecureServerLib DBLib

SecureClientLib.depends = DBLib ParseDataLib
SecureServerLib.depends = DBLib ParseDataLib
