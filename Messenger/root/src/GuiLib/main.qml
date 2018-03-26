import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.3

Window {
    id: window
    width: 300
    height: 200
    visible:true
    title: qsTr("Messenger")

    Connections
    {
        target: gui
        onSignalSuccessConect:
        {
            wConnect.visible = false
            wAuth.visible = true
        }
        onSignalSuccessRegistr:
        {
             wMain.myLogin = login
             window.hide()
             wMain.show()
        }
        onSignalSuccessAuthor:
        {
            wMain.show()
            window.hide()
            wMain.myLogin=login
        }
        onSignalError:
        {
            messageDialog.visible=true
            messageDialog.text=error
        }
    }

    Connection
    {
        id:wConnect
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        onSignalExit:
        {
           gui.connection(ip,port)
        }
    }

    Authorization
    {
        id:wAuth
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible: false
        onSignalRegistration:
        {
            wAuth.visible = false
            wRegistr.visible = true
        }
        onSignalSignIn:
        {
            gui.authirization(login,password)
        }
    }

    Registration
    {
        id:wRegistr
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible:false     
        onSignalSignIn:
        {
           gui.registration(login, password)
        }
        onSignalBack:
        {
            wAuth.visible = true
            wRegistr.visible = false
        }
    }

    MainWindow
    {
        id: wMain
        visible:false
    }

    MessageDialog
    {
        id: messageDialog
        title: "Information"
        visible: false
        onAccepted:
        {
            messageDialog.visible = false
        }
    }
}
