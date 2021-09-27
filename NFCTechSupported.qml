import QtQuick 2.14
Item {
    anchors.fill: parent
    states: [
        State {
            when: NFCReader.targetConnected || (NFCReader.readonce == 1)
            PropertyChanges {
                target: tagConnected
                visible: true
            }
        },
        State {
            when: !NFCReader.targetConnected
            PropertyChanges {
                target: tagNotConnected
                visible: true
            }
        }
    ]

    TagConnectionState{
        id:connectionState
    }

    TagConnected{
        id:tagConnected
    }

    TagNotConnected {
       id:tagNotConnected
    }

}
