import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick 2.6


Window {
    id: wMain

    width: 800
    height: 600


    property string inConversationWith
    property string myLogin

    Connections{

        target: gui

    }


    Rectangle{
        id:recList

        width:200
        height: parent.height-50

        color: "#FAFDFD"
        anchors.top: recMenu.bottom
        anchors.topMargin: 0
        border.color: "#95a4f7"
        border.width: 2

        StackView {
               id: stackView
               width:recList.width
               height: recList.height

               anchors.top: parent.top
               anchors.topMargin: 0

               initialItem:

        ListView {
            id: listView

            Layout.fillWidth: true
            Layout.fillHeight: true
                    spacing: 20
                    // установить список друзей
                    model: gui.dataClients

                    delegate: ItemDelegate
                    {
                        text: modelData.login
                        width: listView.width - listView.leftMargin - listView.rightMargin
                        height: 30

                         onClicked:
                         {
                             gui.choiceFriend(modelData.login)
                             inConversationWith = modelData.login
                             recDialog.visible=true
                         }
                    }

        }



    }
        Button {

            id:butGetList

            text: qsTr("List updates")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            onClicked:
            {
                gui.getListFriends()
            }
    }

    }

    Rectangle{
        id:recDialog

        height: parent.height-50
        visible: false

        color:"#EAFCFA"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: recList.right
        anchors.leftMargin: 0
        anchors.top: recMenu.bottom
        anchors.topMargin: 0

ToolBar {
    id: title

    width:recDialog.width

        Label {
                    text: inConversationWith
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                }
}


ColumnLayout {

    anchors.top: title.bottom
    anchors.right: recDialog.right
    anchors.bottom: recDialog.bottom
    anchors.left: recDialog.left

            ListView {
                y: 60
                height: 430
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: true
                Layout.fillHeight: true

                           verticalLayoutDirection: ListView.BottomToTop
                           spacing: 12
                           model: gui.dataDialog
                           delegate:

                               Column {
                                               anchors.right: sentByMe ? recDialog.right : undefined
                                               spacing: 6

                                               readonly property bool sentByMe: modelData.login !== myLogin

                                               Row {
                                                   id: messageRow
                                                   spacing: 6
                                                   anchors.right: sentByMe ? recDialog.right : undefined


                                                   Rectangle {

                                                       id:recMessange
                                                       color: sentByMe ? "lightgrey" : "steelblue"

                                                       Label {
                                                           id: messageText
                                                           text: modelData.message
                                                           color: sentByMe ? "black" : "white"
                                                           anchors.fill:recMessange
                                                           anchors.margins: 12
                                                       }
                                                   }
                                               }

                                               Label {
                                                   id: timestampText
                                                   text: modelData.time
                                                   color: "lightgrey"
                                                   anchors.right: sentByMe ? recDialog.right : undefined
                                               }
                                           }
                       }

               Pane {
                          id: pane
                          Layout.fillWidth: true

                          RowLayout {
                              width: parent.width

                              TextArea {
                                  id: messageField
                                  Layout.fillWidth: true
                                  placeholderText: qsTr("Compose message")
                                  wrapMode: TextArea.Wrap
                              }

                                // open file
                              Button {
                                  id: butOpenFile
                                  text: qsTr("Browser...")
                                  onClicked: {

                                  }

                              }

                              Button {
                                  id: sendButton
                                  text: qsTr("Send")
                                  enabled: messageField.length > 0
                                  onClicked: {
                                    gui.sendMessage(messageField.text);
                                    messageField.text = "";
                                  }
                              }


                          }
                      }
           }



}

    Rectangle{
        id:recMenu

        width: parent.width
        height:50
        color: "#0d86a8"
        border.color: "#d4e9ef"

        x:0
        y:0

        ToolButton {
            x: 0
            y: 0
            width: 90
            height: 50
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 1
            onClicked:{
                 recDialog.visible=false
            }
        }

        Label {
            width: 200
            text: myLogin
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 20
                }

        ToolButton {
            width: 90
            height: 50
            text: qsTr("Exit")
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: Qt.quit()
        }

    }


}

