import QtQuick

Rectangle {
    id: entryDelegateRoot
    property alias originalText: originalText.text
    property alias translationText: translationText.text
    property int wordType
    property string niche

    height: Math.max(originalRect.height, translationRect.height)
    Rectangle {
        id: originalRect
        implicitHeight: Math.max(originalText.implicitHeight, translationText.implicitHeight)
        width: root.width / 2
        Text {
            id: originalText
            anchors.fill: parent
            wrapMode: TextInput.Wrap
        }
        border.color: "lightblue"
        border.width: 0.5
    }

    Rectangle {
        id: translationRect
        height: originalRect.implicitHeight
        width: root.width / 2
        anchors.left: originalRect.right

        Text {
            id: translationText
            anchors.fill: parent
            wrapMode: TextInput.Wrap
        }
        border.color: "lightblue"
        border.width: 0.5
    }
}
