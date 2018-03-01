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


    signal signalSignIn()   // Задаём сигнал

    Column{
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
            id: row1
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: title.bottom
            anchors.topMargin: 20
            mytext:"Login:"
            focus:true
          }

        MyRow{
            id: row2
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: row1.bottom
            anchors.topMargin: 50
            mytext:"Password:"

        }

        Row{
            id:row3
            anchors.right: parent.right
            anchors.rightMargin: 20


            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: row2.bottom
            anchors.topMargin: 50

            MyButton {
                 id: butSignIn
                 width: 100

                 Layout.fillHeight: true
                 Layout.fillWidth: true


                 text:"Sign in"
                 anchors.horizontalCenter: parent.horizontalCenter
                 onClicked:
                 {
                     // проверка данных
                     //...
                   /*  model.m_login=editLogin.text;
                     model.m_password=editPassword.text;
*/
                     wRegistration.signalSignIn()
                 }
             }
        }
    }



}
