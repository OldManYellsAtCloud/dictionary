import QtQuick

Item {

    property alias originalText: originalText.text
    property alias translationText: translationText.text
    property int wordType
    property string niche

    Text {
        id: originalText
        width: root.width / 2
        height: 30
    }

    Text {
        id: translationText
        text: translation
        width: root.width / 2
        anchors.left: originalText.right
        height: 30
    }
}
