import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

RowLayout{
   property string lblName: ""
   property string lblValue: ""

   width:  parent.width *0.95
   height: parent.height * 0.06
   anchors.horizontalCenter: parent.horizontalCenter
   spacing: 0
   Rectangle
         {
          id:lblNameContainer
          Layout.fillWidth: false
          Layout.preferredWidth: parent.width * 0.30
          Layout.fillHeight: true
          radius: 2
          color: "#daf8e3"//"#daf8e3"

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
                 color: "#0086ad"
                 text: lblName
                 font.pixelSize: 20
                 minimumPixelSize: 15
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
                 }
         }

   Rectangle
        {
       id:lblValueContainer
       Layout.fillWidth: false
       Layout.preferredWidth: parent.width * 0.70
       Layout.fillHeight: true
       radius: 2
       color: "#daf8e3"//"#daf8e3"

             Rectangle
                {
                width: parent.radius
                height: parent.height
                anchors.left: parent.left
                color: parent.color
                }

             Text
                {
                 anchors.fill: parent
                fontSizeMode: Text.Fit
                color:"#00c2c7"
                text: lblValue
                font.pixelSize: 20
                minimumPixelSize: 10
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.capitalization: Font.AllUppercase
                }
        }

}
