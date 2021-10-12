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
        color: "#3b5998"
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
        color: "#3b5998"
        font.pixelSize: 30
        font.capitalization: Font.AllUppercase
        fontSizeMode: Text.Fit
    }
    Image {
           source: NFCReader.isNFCAvailable ? "qrc:/nfcFounding.png" : "qrc:/nfc_off.png"
           anchors.horizontalCenter: parent.horizontalCenter
           width: portaitMode ? sourceSize.width *0.60 : sourceSize.width * 0.30
           height: portaitMode ? sourceSize.height*0.60 : sourceSize.height * 0.30
           anchors.top: lblNFCAvailable.bottom
           anchors.topMargin: lblNFCAvailable.height * 0.15

           SequentialAnimation on opacity {
               running: NFCReader.isNFCAvailable
               loops: Animation.Infinite
               alwaysRunToEnd: true
               PropertyAnimation {
                   from: true
                   to: false
                   duration: 1500
               }
               PropertyAnimation {
                   from: false
                   to: true
                   duration: 1500
               }
           }
        }
}
