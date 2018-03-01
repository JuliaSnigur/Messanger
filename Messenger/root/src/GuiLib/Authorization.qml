import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Item {
    id: wAuthorization
    visible: true
    width: 300
    height: 200


    signal signalSignIn()   // Задаём сигнал
    signal signalRegistration()

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
            text:"Authorization"
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


            MyButton{
                id: butReg

                Layout.fillHeight: true
                Layout.fillWidth: true

                text:"Registration"
               anchors.left: row3.left

               onClicked:
               {
                 wAuthorization.signalRegistration()

               }
            }

            MyButton {
                 id: butSignIn

                 Layout.fillHeight: true
                 Layout.fillWidth: true

                 anchors.right: row3.right

                 text:"Sign in"
                 onClicked:
                 {
                     // проверка данных
                     //...
                   /*  model.m_login=editLogin.text;
                     model.m_password=editPassword.text;
*/
                     wAuthorization.signalSignIn()
                 }
             }
        }
    }



}
