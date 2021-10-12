import QtQuick 2.0

Rectangle {
    id:tagconnectivity
    width: parent.width * 0.95
    height: parent.height * 0.06
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height * 0.02
    radius: 2
    border.color: "transparent"
    border.width: 2

    states: [
        State {
            when : !NFCReader.targetConnected
            PropertyChanges {
                target: tagconnectivity
                color: "transparent"
            }
            PropertyChanges {
                target: txtTagConnectivity
                text:"Tag not connected"
                color: "red"
            }
        },
        State{
            when : NFCReader.targetConnected
            PropertyChanges {
                target: tagconnectivity
                color: "transparent"
            }
            PropertyChanges {
                target: txtTagConnectivity
                text:"Tag connected"
                color: "green"
            }
        }
    ]

    Text {
        id: txtTagConnectivity
        anchors.fill: parent
        fontSizeMode: Text.Fit
        minimumPixelSize: 15
        font.pixelSize: 20
        color: "magenta"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.capitalization: Font.AllUppercase
    }
}
