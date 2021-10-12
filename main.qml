import QtQuick 2.14
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    property bool portaitMode: Screen.desktopAvailableHeight > Screen.desktopAvailableWidth

    background: Rectangle{
          color: "#dfe3ee"
    }

    Item {
       anchors.fill: parent

       states: [
           State {
               when: !NFCReader.isNFCSupported
               PropertyChanges {
                   target: nfcNotSupported
                   visible: true
               }
           },
           State {
               when: NFCReader.isNFCSupported
               PropertyChanges {
                   target: nfcSupported
                   visible: true
               }
           }
       ]

       NFCTechNotSupported {
           id:nfcNotSupported
       }

       NFCTechSupported {
           id:nfcSupported
       }

    }


}
