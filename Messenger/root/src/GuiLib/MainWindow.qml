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
        border.color: "#00000000"
        anchors.top: recMenu.bottom
        anchors.topMargin: 0
        border.width: 2

        StackView {
               id: stackView
               width:recList.width
               height: recList.height
               font.letterSpacing: 0
               font.family: "Times New Roman"
               font.italic: true
               font.pointSize: 16

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
            font.pointSize: 12
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
       // visible: false
        visible: true
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
                    font.family: "Arial"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pixelSize: 20
                        }
        }


ColumnLayout {
    anchors.rightMargin: 8
    anchors.left: parent.left
    anchors.leftMargin: 8

    anchors.top: title.bottom
    anchors.right: recDialog.right
    anchors.bottom: recDialog.bottom

            ListView {
                y: 60
                height: 430
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: true
                Layout.fillHeight: true

                           verticalLayoutDirection: ListView.TopToBottom
                           spacing: 12
                           model: gui.dataDialog
                           delegate:

                               Column {

                                            readonly property bool sentByMe: modelData.flag !== true


                                               anchors.right: sentByMe ? parent.right : undefined
                                               spacing: 6


                                               Row {
                                                   id: messageRow
                                                   spacing: 6
                                                   anchors.right: sentByMe ? parent.right : undefined


                                                   Rectangle {

                                                       id:recMessange

                                                       width: Math.min(messageText.implicitWidth + 24,
                                                              listView.width - (!sentByMe ? 50 + messageRow.spacing : 0))

                                                       height: messageText.implicitHeight + 24



                                                       //height: messageText.implicitHeight + 24
                                                       color: sentByMe ? "lightgrey" : "steelblue"

                                                       Label {
                                                           id: messageText
                                                           text: modelData.message
                                                           color: sentByMe ? "black" : "white"
                                                           anchors.fill:recMessange
                                                           anchors.margins: 12
                                                           wrapMode: Label.Wrap
                                                       }
                                                   }
                                               }

                                               Label {
                                                   id: timestampText
                                                   text: modelData.time
                                                   color: "lightgrey"
                                                   anchors.right: sentByMe ? parent.right : undefined
                                               }

                                               Label {
                                                   id: stateMessText
                                                   text: modelData.stateMess
                                                   color: "red"
                                                   anchors.right: sentByMe ? parent.right : undefined
                                               }
                                           }
                       }

               Pane
               {
                          id: pane
                          Layout.fillWidth: true

                          RowLayout {
                              width: parent.width

                              TextArea {
                                  id: messageField
                                  font.pointSize: 12
                                  horizontalAlignment: Text.AlignLeft
                                  Layout.fillWidth: true
                                  placeholderText: qsTr("Compose message")
                                  wrapMode: TextArea.Wrap
                              }

                                // open file
                              Button
                              {
                                  id: butOpenFile
                                  text: qsTr("Browser...")
                                  font.pointSize: 12
                                  onClicked:
                                  {
                                      fileDialog.visible = true
                                  }

                              }

                              Button {
                                  id: sendButton
                                  text: qsTr("Send")
                                  font.pointSize: 12
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
        color: "#1cc1f5"
        border.color: "#d4e9ef"

        x:0
        y:0

        ToolButton {
            x: 0
            y: 0
            width: 90
            height: 50
            text: qsTr("Back")
            font.pointSize: 12
            anchors.left: parent.left
            anchors.leftMargin: 1
            onClicked:{
                 recDialog.visible=false
            }
        }

        Label {
            width: 200
            text: myLogin
            styleColor: "#f3baba"
            font.bold: true
            renderType: Text.QtRendering
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 25
        }

        ToolButton {
            width: 90
            height: 50
            text: qsTr("Exit")
            font.pointSize: 12
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: Qt.quit()
        }

    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        visible: false
        onAccepted:
        {
            console.log("You chose: " + fileDialog.fileUrls)
            gui.sendFile(fileDialog.fileUrls)
            Qt.quit()
        }
        onRejected:
        {
            console.log("Canceled")
            Qt.quit()
        }
    }


}

