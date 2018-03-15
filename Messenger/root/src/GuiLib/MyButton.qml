import QtQuick 2.0

Rectangle {
    id: mybutton

    //Добавляем к кнопке свойство text,
    //в которое можно будет что-нибудь записать.
    //Это будет текст нашей кнопки
    property string text

    color: "#E6E6E6"

    width:100
    height: 30

    border {
        color: "black"
        width: 1
    }

    //Непосредственно элемент, рисующий текст кнопки
    Text {
        id: buttonText
        //По центру кнопки
        anchors.centerIn: parent
        font.pixelSize: 14
        text: mybutton.text

    }

    signal clicked

    MouseArea {
            anchors.fill: parent

            onPressed: {

                colorChanged("blue")
            }

            onClicked:{

                mybutton.focus=true
                mybutton.clicked()
            }
        }
}
