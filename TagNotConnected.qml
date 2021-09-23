import QtQuick 2.0
import QtQuick.Controls 2.14

Item {
    width: parent.width
    height: parent.height * 0.94
    anchors.bottom: parent.bottom
    visible: false


    Label {
        id: lblNFCAvailable
        visible: NFCReader.isNFCSupported && !NFCReader.isNFCAvailable
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.10
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.90
        height: parent.height * 0.10
        text: NFCReader.nfcNotAvailableMessage
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "#0086ad"
        font.pixelSize: 30
        font.capitalization: Font.AllUppercase
        fontSizeMode: Text.Fit
    }
    Label {
        id: lblNFCStartDetection
        visible: NFCReader.isNFCAvailable && NFCReader.targetDetecting
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.10
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.90
        height: parent.height*0.10
        text: NFCReader.targetDetectingMessage
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "#0086ad"
        font.pixelSize: 30
        font.capitalization: Font.AllUppercase
        fontSizeMode: Text.Fit
    }
}
