import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3


import SignIn 1.0

Window {
    id: wAuthorization
    visible: true
    width: 300
    height: 200
    property alias butSignIn: butSignIn
    property alias editLogin: editLogin
    title: qsTr("Messenger")

    signal signalExit   // Задаём сигнал

    SignIn{
        id: model
    }


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




        Row{
            id: row1
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: title.bottom
            anchors.topMargin: 20


            Text{
                id: labelLog
                width: 70
                text:"Login"
                font.pixelSize: 14
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                }

            Rectangle
            {
                anchors.left: labelLog.right
                anchors.leftMargin: 20
                 border.width: 1

                width:150
                height:20

                 TextInput {
                     id: editLogin
                     clip: true
                     anchors.fill:parent
                     focus: true
                     font.pixelSize: 14

                     anchors.leftMargin: 5
                     anchors.rightMargin: 5

                     wrapMode: TextEdit.Wrap
                    // onCursorRectangleChanged: funcJS.ensureVisible(cursorPosition)

                 }
            }
             }




        Row{
            id: row2
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: row1.bottom
            anchors.topMargin: 50
            Text{
                id:labelPass
                width: 70
                text:"Password"
                font.pixelSize: 14
                }

            Rectangle
            {
                anchors.left: labelPass.right
                anchors.leftMargin: 20
                border.width: 1

                width:150
                height:20
                clip: false

                 TextInput {
                     id: editPassword
                     clip: true
                     focus: true
                     anchors.fill:parent
                     font.pixelSize: 14

                     anchors.leftMargin: 5
                     anchors.rightMargin: 5

                     wrapMode: TextEdit.Wrap
                   //  onCursorRectangleChanged: funcJS.ensureVisible(cursorRectangle)
                      //onCursorRectangleChanged: model.ensureVisible(cursorRectangle)
                 }
             }

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
                   wAuthorization.signalExit() // Вызываем сигнал
                   wRegistration.show()  // Открываем первое окно
                   wAuthorization.hide()   // Скрываем основное окно
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
                     model.m_login=editLogin.text;
                     model.m_password=editPassword.text;
                     model.sendRequestToServer();
                 }
             }
        }
    }



}
