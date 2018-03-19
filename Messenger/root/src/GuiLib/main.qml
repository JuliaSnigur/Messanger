import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.3

Window {
    id: window
    width: 300
    height: 200
    visible:true
    title: qsTr("Messenger")
    Scale:Scale { origin.x: 0; origin.y: 0; xScale: scaleX; yScale: scaleY }

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
             wMain.myLogin=login
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
        visible:false

    }




    MessageDialog {
        id: messageDialog
        title: "Error"
        visible: false

        onAccepted: {
            messageDialog.visible = false
        }
    }


}
