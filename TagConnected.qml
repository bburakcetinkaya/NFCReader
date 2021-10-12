import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


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


    TabView {
        id: tabs

        width: parent.width; height: parent.height
        anchors.top: parent.top

        style: TabViewStyle {
                frameOverlap: 1
                tabsAlignment: Qt.AlignHCenter
                tab: Rectangle {
                    color: styleData.selected ? "#03396c" :"#005b96"
                    implicitWidth: Math.max(text.width + 4, mainrectangle.width/3)
                    implicitHeight: mainrectangle.height * 0.05
                    radius: 2
                    Text {
                        id: text
                        anchors.centerIn: parent
                        text: styleData.title
                        color: styleData.selected ? "#6497b1" : "#b3cde0"
                    }
                }
                 frame: Rectangle {
                     id: tabrectangle
                     color: "transparent" //"transparent" //
                     implicitHeight: mainrectangle.height * 0.025}
              }

            Tab {
            title: "GENERAL"

                Rectangle {
            //property string title: "GENERAL"
            anchors.top: parent.bottom
            anchors.topMargin: parent.height * 0.05
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffffff"


                GeneralInfo {
                    id: generalInfotab
                    anchors.top: parent.top
                    anchors.fill: parent
                    anchors.horizontalCenter: parent.horizontalCenter
                }
              }
            }



       Tab{
           title:"RAW"
           Rectangle {
            id: rawtab
            anchors.top:parent.bottom
            anchors.topMargin: parent.height * 0.05
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffffff"

            RawData {
                   id: rawtabl
                   anchors.top:parent.top
                   anchors.fill: parent
                   anchors.horizontalCenter: parent.horizontalCenter
                    }
                 }
            }

        Tab {
            title: "WRITE"

            Rectangle {
            id: ndeftab
            //property string title: "NDEF"
            anchors.top:parent.bottom
            anchors.topMargin: parent.height * 0.05
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffffff"

                 NdefDataOperations {
                id: ndefdataoperations
                anchors.top:parent.top
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter

            }
          }

       }
    }
  }
}





