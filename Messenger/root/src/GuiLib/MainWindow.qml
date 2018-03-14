import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtBluetooth 5.3

Item {
    id: wtop
/*
    Component.onCompleted: state = "begin"

    property string remoteDeviceName: ""
    property bool serviceFound: false

    BluetoothDiscoveryModel {
        id: btModel
        running: true
        discoveryMode: BluetoothDiscoveryModel.FullServiceDiscovery
        onRunningChanged : {
            if (!btModel.running && wtop.state == "begin" && !serviceFound) {
                searchBox.animationRunning = false;
                searchBox.appendText("\nNo service found. \n\nPlease start server\nand restart app.")
            }
        }

        onErrorChanged: {
            if (error != BluetoothDiscoveryModel.NoError && !btModel.running) {
                searchBox.animationRunning = false
                searchBox.appendText("\n\nDiscovery failed.\nPlease ensure Bluetooth is available.")
            }
        }

        onServiceDiscovered: {
            if (serviceFound)
                return
            serviceFound = true
            console.log("Found new service " + service.deviceAddress + " " + service.deviceName + " " + service.serviceName);
            searchBox.appendText("\nConnecting to server...")
            remoteDeviceName = service.deviceName
            socket.setService(service)
        }
        uuidFilter: targetUuid //e8e10f95-1a70-4b27-9ccf-02010264e9c8
    }

    BluetoothSocket {
        id: socket
        connected: true

        onSocketStateChanged: {
            switch (socketState) {
                case BluetoothSocket.Unconnected:
                case BluetoothSocket.NoServiceSet:
                    searchBox.animationRunning = false;
                    searchBox.setText("\nNo connection. \n\nPlease restart app.");
                    top.state = "begin";
                    break;
                case BluetoothSocket.Connected:
                    console.log("Connected to server ");
                    top.state = "chatActive"; // move to chat UI
                    break;
                case BluetoothSocket.Connecting:
                case BluetoothSocket.ServiceLookup:
                case BluetoothSocket.Closing:
                case BluetoothSocket.Listening:
                case BluetoothSocket.Bound:
                    break;
            }
        }
        onStringDataChanged: {
            console.log("Received data: " )
            var data = remoteDeviceName + ": " + socket.stringData;
            data = data.substring(0, data.indexOf('\n'))
            chatContent.append({content: data})
            console.log(data);
        }
        //...
    }

    ListModel {
        id: chatContent
        ListElement {
            content: "Connected to chat server"
        }
    }

    Rectangle {
        id: background
        z: 0
        anchors.fill: parent
        color: "#5d5b59"
        anchors.leftMargin: 0
    }
    /*
    Search {
        id: searchBox
        anchors.centerIn: top
        opacity: 1
    }

    Rectangle {
        id: chatBox
        opacity: 0
        anchors.centerIn: wtop

        color: "#5d5b59"
        border.color: "black"
        border.width: 1
        radius: 5
        anchors.fill: parent

        function sendMessage()
        {
            // toogle focus to force end of input method composer
            var hasFocus = input.focus;
            input.focus = false;

            var data = input.text
            input.clear()
            chatContent.append({content: "Me: " + data})
            socket.stringData = data
            chatView.positionViewAtEnd()

            input.focus = hasFocus;
        }

        Item {
            anchors.fill: parent
            anchors.margins: 10

            TextField {
                id: input
                Keys.onReturnPressed: chatBox.sendMessage()
                height: sendButton.height
                width: parent.width - sendButton.width - 15
                anchors.left: parent.left
            }

            Button {
                id: sendButton
                anchors.right: parent.right
                text: "Send"
                onClicked: chatBox.sendMessage()
            }

            Rectangle {
                height: parent.height - input.height - 15
                width: parent.width;
                color: "#d7d6d5"
                anchors.bottom: parent.bottom
                border.color: "black"
                border.width: 1
                radius: 5

                ListView {
                    id: chatView
                    width: parent.width-5
                    height: parent.height-5
                    anchors.centerIn: parent
                    model: chatContent
                    clip: true
                    delegate: Component {
                        Text {
                            font.pointSize: 14
                            text: modelData
                        }
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "begin"
            PropertyChanges { target: searchBox; opacity: 1 }
            PropertyChanges { target: chatBox; opacity: 0 }
        },
        State {
            name: "chatActive"
            PropertyChanges { target: searchBox; opacity: 0 }
            PropertyChanges { target: chatBox; opacity: 1 }
        }
    ]

    */
}

