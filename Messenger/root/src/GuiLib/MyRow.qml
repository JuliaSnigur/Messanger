import QtQuick 2.6
import QtQuick.Controls 2.2

Item
{
    id: myRow
    width: 250
    height:30
    property string mytext
    property string editText: edit.text
    Text
    {
       id: label
       height: myRow.height
       text:myRow.mytext
       anchors.verticalCenter: parent.verticalCenter
       anchors.left: parent.left
       anchors.right: edit.left
       anchors.rightMargin: 30
       font.pixelSize: 14
    }
    TextField
    {
      id: edit
      width:150
      text: ""
      height: myRow.height
      anchors.right: parent.right
    }
}
