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


    MyTest{
        id: test
        visible: true

        onSignalExit:
        {
             model.connection();
           // messageDialog.visible=true;
        }
    }


    MessageDialog {
        id: messageDialog
        title: "May I have your attention please"

        text: "It's so cool that you are using Qt Quick."

        onAccepted: {
            console.log("And of course you could only agree.")

        }
        Component.onCompleted: visible = false
    }


  /*  FirstWindow
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
*/

}
