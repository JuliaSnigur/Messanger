import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Item {
    id:test

    visible: true
    width: 300
    height: 200

    signal signalExit()

    MyButton {
        id: but
        width: 100
        height: 30


        text:"Go"
        anchors.verticalCenter: parent.verticalCenter
         anchors.horizontalCenter: parent.horizontalCenter
         clip: true
         visible: true
         anchors.topMargin: 50

         onClicked:
         {
             test.signalExit() // Вызываем сигнал
         }

    }
}
