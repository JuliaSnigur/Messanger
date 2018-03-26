import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item
{
    id: wConncetion
    width: 300
    height: 200
    signal signalExit(string ip , string port)
    MyRow
    {
        id: ipServer
        anchors.right: parent.right
        anchors.rightMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 30
        mytext:"Servers IP:"
    }
    MyRow
    {
        id: port
        anchors.right: parent.right
        anchors.rightMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: ipServer.bottom
        anchors.topMargin: 30
        mytext:"Servers port:"
    }
    Button
    {
        id: but
        text: qsTr("Go")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 100
        font.pointSize: 12
        anchors.top: port.bottom
        anchors.topMargin: 30
        clip: true
        visible: true
        onClicked:
        {
            wConncetion.signalExit(ipServer.editText,port.editText)

        }
    }
}
