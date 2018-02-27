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

        onSignalExit:
        {
            model.m_port=firstWindow.port
            model.m_ip=firstWindow.ip

            firstWindow.visible=false

        }
    }



}
