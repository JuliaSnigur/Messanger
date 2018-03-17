import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2



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

    Button {
        id: but
        text: qsTr("Go")
        font.pointSize: 12
        anchors.top: port.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter

        width: 100
        height: 30

        clip: true
        visible: true

        onClicked:
        {
            wConncetion.signalExit(ipServer.editText,port.editText) // Вызываем сигнал
        }

    }


}
