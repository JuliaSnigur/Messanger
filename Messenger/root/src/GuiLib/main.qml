import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.3

Window {
    id: window
    width: 300
    height: 200
    visible:true
    title: qsTr("Messenger")


    property string errorText

    Connections{

        target: gui

        onSignalSuccessConect:
        {
            wConnect.visible = false
            wAuth.visible = true
        }

        onSignalSuccessRegistr:
        {
             window.hide()
             wMain.show()
        }

        onSignalSuccessAuthor:
        {
            wMain.show()
            window.hide()
        }

        onSignalError:
        {
            messageDialog.visible=true
        }

    }

    Connection{

        id:wConnect
      //  visible: true

        onSignalExit:{

           gui.connection(ip,port)

        }
     }

    Authorization{

        id:wAuth
        visible: false

        onSignalRegistration: {

                wAuth.visible = false
                wRegistr.visible = true
        }

        onSignalSignIn: {

            gui.authirization(login,password)
        }
    }


    Registration{

        id:wRegistr
        visible:false

        onSignalSignIn: {

           gui.registration(login,password)
        }
    }


    MainWindow {
        id: wMain
        visible:true

    }




    MessageDialog {
        id: messageDialog
        title: "Error"

        text: gui.m_error
        visible: false

        onAccepted: {
            messageDialog.visible = false
        }
    }


}
