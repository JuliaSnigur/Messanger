import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import GuiLib 1.0


Window {
    id: window
    visible: true
    width: 300
    height: 200

    title: qsTr("Messenger")


    GuiLib{
        id: model
    }


    FirstWindow
    {
        id:firstWindow
        visible:true

        onSignalExit:
        {

            model.m_ip=ip
            model.m_port=port

            model.connection();

            firstWindow.visible=false
            authorWindow.visible=true
        }
    }

    Authorization
    {
        id:authorWindow
        visible: false

        onSignalRegistration:
        {

            authorWindow.visible=false
            registWindow.visible=true
        }

        onSignalSignIn:
        {
            model.m_login=login
            model.m_password=password

            authorWindow.visible=false
            mainWindow.visible=true
        }

    }


    Registration
    {
        id:registWindow
        visible: false

        onSignalSignIn:
        {

            model.m_login=login
            model.m_password=password

            authorWindow.visible=false
            mainWindow.visible=true
        }
    }


    MainWindow
    {
        id:mainWindow
        visible:false

    }


}
