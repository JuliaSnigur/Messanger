import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3



Item {
    id: windowFirst
    width: 300
    height: 200

 signal signalExit(string ip , string port)   // Задаём сигнал

    MyRow{
        id: ipServer
        x: 12
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 50

        mytext:"Servers IP:"
    }
    MyRow{
        id: port
        x: 12
        anchors.top: ipServer.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 50

        mytext:"Servers port:"
    }

    MyButton {
        id: but
        width: 100
        height: 30

        Layout.fillHeight: true
         Layout.fillWidth: true

         text:"Go"
         anchors.horizontalCenter: parent.horizontalCenter
         opacity: 1
         clip: false
         visible: true
         anchors.top: port.bottom
         anchors.topMargin: 50

         onClicked:
         {
             windowFirst.signalExit(ipServer.editText,port.editText) // Вызываем сигнал
         }
    }
}
