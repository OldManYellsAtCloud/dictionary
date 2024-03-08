import QtQuick

Rectangle {
    id: entryDelegateRoot
    property alias originalText: originalText.text
    property alias translationText: translationText.text
    property int wordType
    property string niche

    height: 30
    Text {
        id: originalText
        width: root.width / 2
        height: 30
        wrapMode: TextInput.Wrap
    }

    Text {
        id: translationText
        text: translation
        width: root.width / 2
        anchors.left: originalText.right
        height: 30
        wrapMode: TextInput.Wrap
    }
}
