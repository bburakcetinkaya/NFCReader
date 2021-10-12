import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Item {
    property string lblName: ""
    anchors.horizontalCenter: parent.horizontalCenter

    Rectangle
          {
           id:lblNameContainer
           Layout.fillWidth: false
           Layout.preferredWidth: parent.width * 0.20
           Layout.fillHeight: true
           radius: 2
           color: "transparent"//"#daf8e3"

            Rectangle
                  {
                  width: parent.radius
                  height: parent.height
                  anchors.right: parent.right
                  color: parent.color
                  }

             Text
                  {
                  anchors.fill: parent
                  fontSizeMode: Text.Fit
                  color: "#3b5998" //#3b5998
                  text: lblName
                  font.pixelSize: 20
                  minimumPixelSize: 15
                  horizontalAlignment: Text.AlignHCenter
                  verticalAlignment: Text.AlignVCenter
                  }
          }
         }


