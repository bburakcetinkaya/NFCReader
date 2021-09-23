import QtQuick 2.0
import QtQuick.Controls 2.14

Rectangle {

  width: parent.width * 0.95
  height: parent.height *0.10
  anchors.horizontalCenter: parent.horizontalCenter
  radius: 1
  color: "black" //"#daf8e3"
  visible: NFCReader.targetError !== "" ? true : false

  Label {
      id: trgtError
      anchors.bottom: parent.bottom
      anchors.bottomMargin: parent.height *0.10
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width * 0.90
      height: parent.height * 0.10
      text: NFCReader.targetError
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "darkorange"
      fontSizeMode: Text.Fit
      minimumPixelSize: 15
      font.pixelSize: 22
      font.bold: true
      font.capitalization: Font.AllUppercase

  }
}
