import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2


//import Presenter 1.0

//import "../GuiLib/functions.js" as funcJS

Window {
    id: window
    visible: true
    width: 300
    height: 200
    property alias butSignIn: butSignIn
    property alias editLogin: editLogin
    title: qsTr("Messenger")


  /*  SignIn{
        id: model
    }
*/


    Column{
        id: column
        width: 300
        height: 200
        anchors.top: parent.top
        anchors.topMargin: 0


        Text{
            id:title
            x:parent.height/2
            anchors.topMargin: 20
            text:"Messenger"
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


            Button{
                id: butSignIn

                width:100
                height: 30

                font.pixelSize: 14
                text:"Registration"
               anchors.left: row3.left



            }
            Button{
            id: butReg
            width:100
            height: 30
            font.pixelSize: 14
            text:"Sign in"
            anchors.right: row3.right

         //   onClicked: model.sendInfoOnServer(editLogin.text,editPassword.text)

            }
        }



//import "functions.js"

 Authorization{

        id:windowAuthorization

/*
    Registration{
        id:windowRegistration


    }

*/



    }


}
}
