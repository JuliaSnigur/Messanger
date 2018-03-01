import QtQuick 2.0

Item {
    id: myRow

    //Добавляем к кнопке свойство text,
    //в которое можно будет что-нибудь записать.
    //Это будет текст нашей кнопки
    property string mytext
    property string editText: edit.text

    Row{
        id: row

        Text{
            id: label
            width: 70
            text:myRow.mytext
            font.pixelSize: 14
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            }

        Rectangle
        {
            anchors.left: label.right
            anchors.leftMargin: 20
             border.width: 1

            width:150
            height:20

             TextInput {
                 id: edit
                 clip: true
                 anchors.fill:parent
                 focus: true
                 font.pixelSize: 14

                 anchors.leftMargin: 5
                 anchors.rightMargin: 5
             }
        }
         }

}
