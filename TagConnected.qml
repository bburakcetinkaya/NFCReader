import QtQuick 2.0
import QtQuick.Controls 2.15


Item {
    width: parent.width
    height: parent.height
    anchors.bottom: parent.bottom
    visible: false


    Rectangle {
        id: mainrectangle
        width: parent.width
        height: parent.height
        anchors.top: parent.top

    TabWidget {
        id: tabs
        width: parent.width
        height: parent.height

        Rectangle {
        property string title: "General"
       // property string color: "#107dac"
        anchors.fill: parent
        color: "#ffffff"


        InfoTagRow{
            id: targetUIDLbl
            lblName: "NFC UID:"
            lblValue: NFCReader.targetUID
            anchors.top:parent.top
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

              RoundButton {
              id:newscanbutton
              anchors.bottom: parent.bottom
              anchors.bottomMargin: parent.height * 0.03
              anchors.horizontalCenter: parent.horizontalCenter
              text: "New Scan"
              onClicked: NFCReader.readonce = 0
              background: Rectangle{
                                color: "#8b9dc3"

                }
            }

        TagErrorField{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height * 0.10
                }
            }//GENERAL END
       //-----------------------------------------------------------------------------------
        Rectangle {
           id: rawtab
           property string title: "RAW"
           anchors.fill: parent
           color: "#ffffff"
           TabWidget {
               id: rawdatatabs
               width: parent.width
               height: parent.height
                 Rectangle {
                     id:hextab
                     property string title: "HEX"
                     anchors.fill: parent
                     color: "#ffffff"
                     InfoTagRow{
                                 id: targetBlockRead
                                 lblName: "sector1:"
                                 lblValue: NFCReader.targetBlock
                                 anchors.top:parent.top
                                 anchors.topMargin: parent.height * 0.02
                             }


                 }//HEW TAB END
                 Rectangle {
                     id: asciitab
                     property string title: "ASCII"
                     anchors.fill: parent
                     color: "#ffffff"
                     InfoTagRow{
                                 id: targetBlockAsString
                                 lblName: "sector1:"
                                 lblValue: NFCReader.targetBlockAsString
                                 anchors.top:parent.top
                                 anchors.topMargin: parent.height * 0.02
                             }
                   }//ASCII TAB END

         }//RAW DATA TAB WIDGET TABS END
        }//RAW TAB RECTANGLE END
       //-----------------------------------------------------------------------------------




       Rectangle {
          id: ndeftab
          property string title: "NDEF"
          anchors.fill: parent
          color: "#ffffff"
          TabWidget {
              id: ndeftabs
              width: parent.width
              height: parent.height
                Rectangle {
                    id:readtab
                    property string title: "READ"
                    anchors.fill: parent
                    color: "#ffffff"
                          /*  InfoTagRow{
                                id: ndefmessage1
                                lblName: "Message1:"
                                lblValue: NFCReader.readNdefMessagesSend
                                anchors.top: parent.top
                                anchors.topMargin: parent.height * 0.02

                            }*/

                }//NDEF READ END

                Rectangle {
                    id: writetab
                    property string title: "WRITE"
                    anchors.fill: parent
                    color: "#ffffff"
                  }//NDEF WRITE END

        }//NDEF TABS END
       }//NDEF TAB RECTANGLE END

      }//TABS END
   }
}
