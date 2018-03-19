import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3


Item {
    id: wRegistration
    visible: true
    width: 300
    height: 200


    signal signalSignIn(string login,string password)   // Задаём сигнал


    Rectangle{
        id: column
        width: 300
        height: 184
        anchors.top: parent.top
        anchors.topMargin: 10


        Text{
            id:title
            x:parent.height/2
            anchors.topMargin: 20
            text:"Registration"
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
            id:row3
            anchors.horizontalCenter: parent.horizontalCenter


            anchors.top: password.bottom
            anchors.topMargin: 20

            MyButton {
                 id: butSignIn
                 width: 100

                 Layout.fillHeight: true
                 Layout.fillWidth: true


                 text:"Sign in"
                 anchors.top: parent.top
                 anchors.topMargin: 0
                 anchors.horizontalCenter: parent.horizontalCenter
                 onClicked:
                 {
                     // проверка данных
                     //...
                     wRegistration.signalSignIn(login.editText,password.editText)
                 }
             }
        }
    }



}
