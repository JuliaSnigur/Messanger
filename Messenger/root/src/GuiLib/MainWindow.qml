import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick 2.6


Window
{
    id: wMain
    width: 800
    height: 600
    property alias sendButton: sendButton
    property alias flick: flick
    property alias pane: pane
    property alias recMenu: recMenu
    property string inConversationWith
    property string myLogin
    Connections
    {
        target: gui

        onSignalSuccessSendFile:
        {
            butOpenFile.enabled = true
        }
    }
    Rectangle
    {
        id:recList
        width:200
        height: parent.height-50
        color: "#FAFDFD"
        border.color: "#00000000"
        anchors.top: recMenu.bottom
        anchors.topMargin: 0
        border.width: 2
        StackView
        {
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
            ListView
            {
              id: listView
              Layout.fillWidth: true
              Layout.fillHeight: true
              spacing: 20
              model: gui.dataClients
              delegate: ItemDelegate
              {
                  id: del
                  readonly property bool flag: modelData.status === true
                  text: modelData.login
                   width: listView.width - listView.leftMargin - listView.rightMargin
                   height: 30
                   leftPadding: avatar.implicitWidth + 35
                   Rectangle
                   {
                      id: avatar
                      x: 5
                      y: 5
                      width: 20
                      height: 20
                      color: flag ? "steelblue" : "lightgrey"
                    }
                    onClicked:
                    {
                        if(modelData.status === true)
                        {
                                 gui.choiceFriend(modelData.id)
                                 inConversationWith = modelData.login
                                 recDialog.visible = true
                        }
                        else
                                 recDialog.visible = false
                    }
                    }

        }



    }
        Button
        {
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


    ToolBar
    {
        id: title
        anchors.top: recMenu.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: recList.right
        anchors.leftMargin: 0

        Label
        {
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


    Rectangle
    {
        id:recDialog
        visible: false
       // visible: true
        color:"#EAFCFA"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: recList.right
        anchors.leftMargin: 0
        anchors.top: title.bottom
        anchors.topMargin: 0

        ColumnLayout
        {
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            anchors.bottomMargin: 0
            visible: true
            anchors.fill: parent
            anchors.topMargin: title.height
            ListView
            {
                y: 150
                height: 430
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: true
                Layout.fillHeight: true
                verticalLayoutDirection: ListView.TopToBottom
                spacing: 12
                model: gui.dataDialog

                delegate:
                Column
                {
                    readonly property bool sentByMe: modelData.flag !== true
                    anchors.right: sentByMe ? parent.right : undefined
                    spacing: 6
                    Row
                    {
                         id: messageRow
                         spacing: 6
                         anchors.right: sentByMe ? parent.right : undefined
                         Rectangle
                         {
                              id:recMessange
                              width: Math.min(messageText.implicitWidth + 24,
                                         listView.width - (!sentByMe ? 50 + messageRow.spacing : 0))
                              height: messageText.implicitHeight + 24
                              color: sentByMe ? "lightgrey" : "steelblue"
                              Label
                              {
                                  id: messageText
                                  text: modelData.message
                                  color: sentByMe ? "black" : "white"
                                  anchors.fill:recMessange
                                  anchors.margins: 12
                                  wrapMode: Label.Wrap
                               }
                          }
                }
                Label
                {
                    id: timestampText
                    text: modelData.time
                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
                }
          }
   }

  Pane
  {
     id: pane
     Layout.fillWidth: true
     height: 40
     RowLayout
     {
         id: rowLayout
         height: 40
         anchors.left: parent.left
         anchors.leftMargin: 0
         anchors.right: parent.right
         anchors.rightMargin: 0
         transformOrigin: Item.Left
         Layout.fillWidth: true
         Layout.fillHeight: true
         Flickable
         {
             id: flick
             Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
             Layout.fillWidth:true
             Layout.fillHeight: true
             contentWidth: messageField.paintedWidth
             contentHeight: messageField.paintedHeight
             function ensureVisible(r)
             {
                if (contentX >= r.x)
                  contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                   contentX = r.x+r.width-width;
                if (contentY >= r.y)
                   contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                   contentY = r.y+r.height-height;
             }
             TextEdit
             {
                 id: messageField
                 height: 40
                 anchors.left: parent.left
                 anchors.leftMargin: 1
                 transformOrigin: Item.Right
                 anchors.verticalCenterOffset: 10
                 anchors.verticalCenter: parent.verticalCenter
                focus: true
                clip: true
                font.pointSize: 12
                wrapMode: TextEdit.Wrap
                onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                property string placeholderText: "Enter text here..."
                Layout.fillWidth: true
                width: 349
                 Text
                 {
                    height: 19
                    text: messageField.placeholderText
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 12
                    color: "#aaa"
                    visible: !messageField.text
                }
           }
        }
        Button
        {
            id: butOpenFile
            x: 0
            width: 100
            text: qsTr("Browser...")
            Layout.fillWidth: false
            opacity: 1
            Layout.rowSpan: 1
            clip: true
            Layout.fillHeight: true
            transformOrigin: Item.Right
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            font.pointSize: 12
            enabled: true
            onClicked:
            {
               fileDialog.visible = true
            }
        }
        Button
        {
             id: sendButton
             x: 0
             width: 100
             height: 40
             text: qsTr("Send")
             Layout.fillWidth: false
             focusPolicy: Qt.ClickFocus
             clip: true
             Layout.fillHeight: true
             transformOrigin: Item.Right
             Layout.alignment: Qt.AlignLeft | Qt.AlignBottom

             enabled: messageField.length > 0
             font.pointSize: 12
             onClicked:
             {
                 gui.sendMessage(messageField.text);
                 messageField.text = "";
             }
        }
     }
  }
 }

}
    Rectangle
    {
        id:recMenu
        width: parent.width
        height:50
        color: "#1cc1f5"
        border.color: "#d4e9ef"
        x:0
        y:0
        ToolButton
        {
            x: 0
            y: 0
            width: 90
            height: 50
            text: qsTr("Back")
            font.pointSize: 12
            anchors.left: parent.left
            anchors.leftMargin: 1
            onClicked:
            {
                 inConversationWith = ""
                 recDialog.visible=false
            }
        }
        Label
        {
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
        ToolButton
        {
            width: 90
            height: 50
            text: qsTr("Exit")
            font.pointSize: 12
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: Qt.quit()
        }

    }
    FileDialog
    {
        id: fileDialog
        title: "Please choose a file"
        visible: false
        onAccepted:
        {
            console.log("You chose: " + fileDialog.fileUrls)
            gui.sendFile(fileDialog.fileUrls)
            fileDialog.visible = false
            butOpenFile.enabled = false
            sendButton.enabled = false
        }
        onRejected:
        {
            console.log("Canceled")
            fileDialog.visible = false
        }
    }
}

