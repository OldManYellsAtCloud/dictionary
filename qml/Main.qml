import QtQuick
import QtQuick.Controls

import sgy.pine.dictionary

Window {
    id:root
    visible: true
    title: qsTr("DE/EN - EN/DE Dictionary")

    EntryModel {
        id: entryModel
    }

    RadioButton {
        id: deRadio
        checked: true
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: enRadio.left
        height: 50
        width: parent.width / 2

        indicator: Rectangle {
            anchors.fill: parent
            color: parent.checked ? "#17a81a" : "#21be2b"
            border.width: 3
            border.color: parent.checked ? "#888f8a" : "#bcc4bf"
            radius: 2
            Text {
                text: qsTr("German")
                anchors.centerIn: parent
            }
        }

        onCheckedChanged: {
            if (checked)
                entryModel.switchLanguage("de");
        }
    }

    RadioButton {
        id: enRadio
        checked: false
        anchors.top: parent.top
        anchors.right: parent.right
        height: 50
        width: parent.width / 2

        indicator: Rectangle {
            anchors.fill: parent
            color: parent.checked ? "#17a81a" : "#21be2b"
            border.width: 3
            border.color: parent.checked ? "#888f8a" : "#bcc4bf"
            radius: 2
            Text {
                text: qsTr("English")
                anchors.centerIn: parent
            }
        }

        onCheckedChanged: {
            if (checked)
                entryModel.switchLanguage("en");
        }
    }


    Rectangle {
        id: textInputBackground
        color: "lightgrey"
        anchors.top: deRadio.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height: 50

        Button {
            id: deleteButton
            height: parent.height
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: parent.height
            Text {
                text: "X"
                font.pixelSize: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked: {
                textInput.clear()
            }
        }

        TextInput {
            id: textInput
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: deleteButton.left
            font.pixelSize: 30
            height: 50
            cursorVisible: true
            inputMethodHints: Qt.ImhNoAutoUppercase

            onTextChanged: {
                if (text)
                    entryModel.getTranslations(text);
            }
        }
    }

    ListView {
        id: entryList
        anchors.top: textInputBackground.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: entryModel
        visible: !(textInput.text === "")

        delegate: EntryDelegate {
            originalText: model.originalText
            translationText: model.translationText
            niche: model.niche
            wordType: model.entryType
        }

    }

}
