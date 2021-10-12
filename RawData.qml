import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.14

Item {

    width: parent.width
    height: parent.height
    anchors.bottom: parent.bottom
    visible: true
    property int current: 0

        SwipeView {
            id: datapart
            currentIndex: 0
            anchors.fill: parent
           Item {
                id: hexpage
                property int current: 0

                Rectangle
                      {
                       id:lblNameforhex
                       Layout.fillWidth: true
                       Layout.preferredWidth: parent.width * 0.20
                       Layout.fillHeight: true
                       radius: 2
                       anchors.horizontalCenter: parent.horizontalCenter
                       color: "#3b5998"

                        Rectangle
                              {
                              width: parent.radius
                              height: parent.height
                              anchors.top: parent.top
                              color: parent.color
                              }

                         Text
                              {
                              anchors.fill: parent
                              fontSizeMode: Text.Fit
                              color: "black"
                              text: "HEX"
                              font.pixelSize: 20
                              minimumPixelSize: 15
                              horizontalAlignment: Text.AlignHCenter
                              verticalAlignment: Text.AlignVCenter
                              }
                        }
               /* HeaderModel{
                    id: lblNameforhex
                    lblName: "HEX"
                    anchors.top: parent.top
                    anchors.topMargin: parent.height * 0.01
                }*/
        InfoTagRow{
            id: targetBlockRead
            lblName: "sector1:"
            lblValue: NFCReader.targetBlock
            anchors.top: lblNameforhex.bottom
            anchors.topMargin: parent.height * 0.02
        }

        InfoTagRow{
            id: targetBlockRead2
            lblName: "sector2:"
            lblValue: NFCReader.targetBlock2
            anchors.top:targetBlockRead.bottom
            anchors.topMargin: parent.height * 0.01
        }

        InfoTagRow{
            id: targetBlockRead3
            lblName: "sector3:"
            lblValue: NFCReader.targetBlock3
            anchors.top:targetBlockRead2.bottom
            anchors.topMargin: parent.height * 0.01
        }

        InfoTagRow{
            id: targetBlockRead4
            lblName: "sector4"
            lblValue: NFCReader.targetBlock4
            anchors.top:targetBlockRead3.bottom
            anchors.topMargin: parent.height * 0.01
        }

        InfoTagRow{
            id: targetBlockRead5
            lblName: "sector5"
            lblValue: NFCReader.targetBlock5
            anchors.top:targetBlockRead4.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockRead6
            lblName: "sector6"
            lblValue: NFCReader.targetBlock6
            anchors.top:targetBlockRead5.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockRead7
            lblName: "sector7"
            lblValue: NFCReader.targetBlock7
            anchors.top: targetBlockRead6.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockRead8
            lblName: "sector8"
            lblValue: NFCReader.targetBlock8
            anchors.top:targetBlockRead7.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockRead9
            lblName: "sector9"
            lblValue: NFCReader.targetBlock9
            anchors.top:targetBlockRead8.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockRead10
            lblName: "sector10"
            lblValue: NFCReader.targetBlock10
            anchors.top:targetBlockRead9.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockRead11
            lblName: "sector11"
            lblValue: NFCReader.targetBlock11
            anchors.top:targetBlockRead10.bottom
            anchors.topMargin: parent.height * 0.01
                }//SECTOR11 HEX END
        Rectangle
              {
               id:swipeRightForAscii
               Layout.fillWidth: true
               Layout.preferredWidth: parent.width * 0.20
               Layout.fillHeight: true
               radius: 2
               anchors.bottom: parent.bottom
               anchors.bottomMargin: parent.height * 0.05
               anchors.horizontalCenter: parent.horizontalCenter
               color: "#3b5998"

                Rectangle
                      {
                      width: parent.radius
                      height: parent.height
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: parent.height * 0.05
                      color: "transparent"
                      }

                 Text
                      {
                      anchors.fill: parent
                      fontSizeMode: Text.Fit
                      color: "black"
                      text: "SLIDE RIGHT FOR ASCII \n ----->"
                      font.pixelSize: 20
                      minimumPixelSize: 15
                      horizontalAlignment: Text.AlignHCenter
                      verticalAlignment: Text.AlignVCenter
                      }
                }
    }//PAGE END


           Item {
                id: asciipage
                property int current:1

                Rectangle
                      {
                       id:lblNameforascii
                       Layout.fillWidth: true
                       Layout.preferredWidth: parent.width * 0.20
                       Layout.fillHeight: true
                       radius: 2
                       color: "#3b5998"
                       anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle
                              {
                              width: parent.radius
                              height: parent.height
                              anchors.topMargin: parent.height * 0.02
                              anchors.top: parent.top
                              color: parent.color
                              }

                         Text
                              {
                              anchors.fill: parent
                              fontSizeMode: Text.Fit
                              color: "#3b5998" //#3b5998
                              text: "ASCII"
                              font.pixelSize: 20
                              minimumPixelSize: 15
                              horizontalAlignment: Text.AlignHCenter
                              verticalAlignment: Text.AlignVCenter
                              }
                        }

        InfoTagRow{
            id: targetBlockAsString
            lblName: "sector1:"
            lblValue: NFCReader.targetBlockAsString
            anchors.top: lblNameforascii.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString2
            lblName: "sector2:"
            lblValue: NFCReader.targetBlockAsString2
            anchors.top: targetBlockAsString.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString3
            lblName: "sector3:"
            lblValue: NFCReader.targetBlockAsString3
            anchors.top:targetBlockAsString2.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString4
            lblName: "sector4:"
            lblValue: NFCReader.targetBlockAsString4
            anchors.top: targetBlockAsString3.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString5
            lblName: "sector5:"
            lblValue: NFCReader.targetBlockAsString5
            anchors.top: targetBlockAsString4.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString6
            lblName: "sector6:"
            lblValue: NFCReader.targetBlockAsString6
            anchors.top: targetBlockAsString5.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString7
            lblName: "sector7:"
            lblValue: NFCReader.targetBlockAsString7
            anchors.top: targetBlockAsString6.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString8
            lblName: "sector8:"
            lblValue: NFCReader.targetBlockAsString8
            anchors.top: targetBlockAsString7.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString9
            lblName: "sector9:"
            lblValue: NFCReader.targetBlockAsString9
            anchors.top: targetBlockAsString8.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString10
            lblName: "sector10:"
            lblValue: NFCReader.targetBlockAsString10
            anchors.top: targetBlockAsString9.bottom
            anchors.topMargin: parent.height * 0.01
        }
        InfoTagRow{
            id: targetBlockAsString11
            lblName: "sector11:"
            lblValue: NFCReader.targetBlockAsString11
            anchors.top: targetBlockAsString10.bottom
            anchors.topMargin: parent.height * 0.01
        }
        Rectangle
              {
               id:swipeLeftForHEX
               Layout.fillWidth: true
               Layout.preferredWidth: parent.width * 0.20
               Layout.fillHeight: true
               radius: 2
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.bottom: parent.bottom
               anchors.bottomMargin: parent.height * 0.05
               color: "#3b5998"

                Rectangle
                      {
                      width: parent.radius
                      height: parent.height
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: parent.height * 0.05
                      color: "transparent"
                      }

                 Text
                      {
                      anchors.fill: parent
                      fontSizeMode: Text.Fit
                      color: "#3b5998"
                      text: "SLIDE LEFT FOR HEX \n <-----"
                      font.pixelSize: 20
                      minimumPixelSize: 15
                      horizontalAlignment: Text.AlignHCenter
                      verticalAlignment: Text.AlignVCenter
                      }
                }

   }//ASCII END
 }//SWIPE RAW END
        PageIndicator {
            id: indicator

            count: datapart.count
            currentIndex: datapart.currentIndex

            anchors.bottom: datapart.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

} //ITEM END
        /* PageIndicator {
    id: indicator

    count: parrent.count
    currentIndex: parrent.currentIndex

    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    }
}*/

