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
    signal signalBack()

    Rectangle
    {
        id: column
        anchors.fill: parent
        Text
        {
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
        MyRow
        {
            id: password
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: login.bottom
            anchors.topMargin: 20
            mytext:"Password:"
        }
        Item
        {
            id:row3
            height: 30
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: password.bottom
            anchors.topMargin: 20
            Button
            {
                id: butBack
                width: 100
                text: qsTr("Back")
                font.pointSize: 12
                anchors.top: parent.top
                anchors.topMargin: 0
                height: 30
                clip: true
                visible: true
                onClicked:
                {
                     wRegistration.signalBack()

                }
            }
            Button
            {
                id: butSignIn
                x: 157
                text: qsTr("Sign in")
                font.pointSize: 12
                anchors.top: parent.top
                anchors.topMargin: 0
                width: 100
                height: 30
                clip: true
                visible: true
                onClicked:
                {
                     wRegistration.signalSignIn(login.editText,password.editText)
                }
            }
        }
    }
}
