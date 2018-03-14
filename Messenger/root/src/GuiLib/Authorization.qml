import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Item {
    id: wAuthorization
    visible: true
    width: 300
    height: 200


    signal signalSignIn(string login,string password)   // Задаём сигнал
    signal signalRegistration()

    Rectangle{
        id: column
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 10


        Text{
            id:title
            x:parent.height/2
            anchors.topMargin: 20
            text:"Authorization"
            font.pixelSize: 24
        }

        MyRow
        {
            id: login
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: title.bottom
            anchors.topMargin: 20
            mytext:"Login:"
            focus:true
          }


        MyRow{
            id: password
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: login.bottom
            anchors.topMargin: 20
            mytext:"Password:"

        }



        Item{
            id:buttons
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20


            anchors.top: password.bottom
            anchors.topMargin: 20


            MyButton{
                id: butReg

                Layout.fillHeight: true
                Layout.fillWidth: true

                text:"Registration"


               onClicked:
               {
                 wAuthorization.signalRegistration()

               }
            }

            MyButton {
                 id: butSignIn

                 Layout.fillHeight: true
                 Layout.fillWidth: true

                 anchors.right: parent.right

                 text:"Sign in"
                 anchors.rightMargin: 0

                 onClicked:
                 {
                     wAuthorization.signalSignIn(login.editText,password.editText)
                 }
             }
        }
    }



}
