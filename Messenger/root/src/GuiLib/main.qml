import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.3

Window {
    id: window
    width: 300
    height: 200
    visible:true
    title: qsTr("Messenger")


    Connection{

        id:wConnect
        visible: true

        onSignalExit:{

           gui.connection(ip,port)

            if(gui.flag)
            {
                wConnect.visible=false
                mAuthorization.visible=true
            }
            else
            {

            }

          // client.slotHello()
        }
     }



    Authorization{

        id:mAuthorization
        visible: false

        onSignalRegistration: {

            mAuthorization.visible=false
            mRegistration.visible=true
        }

        onSignalSignIn: {

            //client.slotAuthorization(login,password)
        }
    }


    Registration{

        id:mRegistration
        visible:false
        onSignalSignIn: {

         // client.slotAuthorization(login,password)
        }
    }



    MessageDialog {
        id: messageDialog
        title: "Error"

        text: gui.m_error
        visible: gui.m_flag

        onAccepted: {
            messageDialog.visible=false
        }
    }


}
