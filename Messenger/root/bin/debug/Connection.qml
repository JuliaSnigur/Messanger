import QtQuick 2.0
import QtQuick.Window 2.10
//import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3



Item {
    id: wConncetion
    width: 300
    height: 200

 signal signalExit(string ip , string port)   // Задаём сигнал

    MyRow{
        id: ipServer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
        mytext:"Servers IP:"
    }
    MyRow{
        id: port
        anchors.top: ipServer.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
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
         anchors.topMargin: 20

         onClicked:
         {
             wConncetion.signalExit(ipServer.editText,port.editText) // Вызываем сигнал
         }
    }
}
