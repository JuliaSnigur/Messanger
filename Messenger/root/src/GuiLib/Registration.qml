import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import SignIn 1.0


Window{

    id: wRegistration
    visible: true
    width: 300
    height: 250
    property alias butSignIn: butSignIn
    property alias editLogin: editLogin
    title: qsTr("Messenger")

    SignIn{
        id: model
    }


    Column{
        id: column
        width: 300
        height: 173
        anchors.top: parent.top
        anchors.topMargin: 0


        Text{
            id:title
            x:parent.height/2
            anchors.topMargin: 20
            text:"Registration"
            font.pixelSize: 24
        }


        Row{
            id: row0
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: title.bottom
            anchors.topMargin: 30


            Text{
                id: labelIP
                width: 70
                text:"IP"
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 14
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                }

            Rectangle
            {
                anchors.left: labelIP.right
                anchors.leftMargin: 20
                 border.width: 1

                width:150
                height:20

                 TextInput {
                     id: editIP
                     clip: true
                     anchors.fill:parent
                     focus: true
                     font.pixelSize: 14

                     anchors.leftMargin: 5
                     anchors.rightMargin: 5

                     wrapMode: TextEdit.Wrap

                 }
            }
             }

        Row{
            id: row1
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: row0.bottom
            anchors.topMargin: 50


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
            anchors.rightMargin: 10


            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: row2.bottom
            anchors.topMargin: 50


            MyButton{
                id: butReg

                Layout.fillHeight: true
                Layout.fillWidth: true

                 x:parent.height/2

                text:"Registration"
               anchors.left: row3.left



               onClicked: {
                   // проверка данных
                   //...
                   model.m_ip=editIP.text;
                   model.m_login=editLogin.text;
                   model.m_password=editPassword.text;
                   model.sendRequestToServer();
               }
            }

        }
    }





    }






