import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.14

Item {
    width: parent.width
    height: parent.height
    anchors.bottom: parent.bottom
    visible: true
        Rectangle {
            id: rectangle
            width: parent.width
            height: parent.height
            anchors.top: parent.top

    Rectangle
          {
           id:lblNameforgeneralInfo
           Layout.fillWidth: false
           Layout.preferredWidth: parent.width * 0.20
           Layout.fillHeight: true
           radius: 2
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.topMargin: parent.height * 0.02
           color: "#3b5998"

            Rectangle
                  {
                  width: parent.radius
                  height: parent.height
                  anchors.top: parent.bottom
                  color: parent.color
                  }

             Text
                  {
                  anchors.fill: parent
                  fontSizeMode: Text.Fit
                  color: "black"
                  text: "GENERAL INFO"
                  font.pixelSize: 20
                  minimumPixelSize: 15
                  horizontalAlignment: Text.AlignHCenter
                  verticalAlignment: Text.AlignVCenter
                  }
          }




        InfoTagRow{
            id: targetUIDLbl
            lblName: "NFC UID:"
            lblValue: NFCReader.targetUID
            anchors.top:lblNameforgeneralInfo.top
            anchors.topMargin: parent.height * 0.02
        }

        InfoTagRow{
            id: targetType
            lblName: "NFC TYPE:"
            lblValue: NFCReader.targetType
            anchors.top:targetUIDLbl.bottom
            anchors.topMargin: parent.height * 0.02
        }

        InfoTagRow{
            id: targetAccessMethod
            lblName: "NFC A.M.:"
            lblValue: NFCReader.targetAccessMethod
            anchors.top:targetType.bottom
            anchors.topMargin: parent.height * 0.02
        }
        InfoTagRow{
            id: doHaveNdefMessage
            lblName: "NDEF: "
            lblValue: if(NFCReader.doHaveNdefMessage == true){"FOUND"} else {"NOT FOUND"}
            anchors.top:targetAccessMethod.bottom
            anchors.topMargin: parent.height * 0.02
        }
        InfoTagRow{
            id: lastInteracted
            lblName: "Last\nInteracted: "
            lblValue: NFCReader.lastInteracted
            anchors.top:doHaveNdefMessage.bottom
            anchors.topMargin: parent.height * 0.02
        }
        InfoTagRow{
            id: latitude
            lblName: "Latitude: "
            lblValue: NFCReader.readCoordinatesLatitude
            anchors.top:lastInteracted.bottom
            anchors.topMargin: parent.height * 0.02
        }
        InfoTagRow{
            id: longtitude
            lblName: "Longitude: "
            lblValue: NFCReader.readCoordinatesLongitude
            anchors.top:latitude.bottom
            anchors.topMargin: parent.height * 0.02
        }


        TagErrorField{
                id: errorfield
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height * 0.15
                }

              RoundButton {
              id:newscanbutton
              anchors.top: errorfield.bottom
              anchors.topMargin: parent.height * 0.03
              anchors.horizontalCenter: parent.horizontalCenter
              text: "New Scan"
              onClicked: NFCReader.readonce = 0

            }
    }


}//GENERAL END
