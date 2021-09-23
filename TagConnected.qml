import QtQuick 2.0
import QtQuick.Controls 2.14

Item {
    width: parent.width
    height: parent.height * 0.92
    anchors.bottom: parent.bottom
    visible: false

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
        id: targetBlockRead
        lblName: "sector1:"
        lblValue: NFCReader.targetBlock
        anchors.top:targetAccessMethod.bottom
        anchors.topMargin: parent.height * 0.02
    }
    InfoTagRow{
        id: targetBlockRead2
        lblName: "sector2:"
        lblValue: NFCReader.targetBlock2
        anchors.top:targetBlockRead.bottom
        anchors.topMargin: parent.height * 0.02
    }
    InfoTagRow{
        id: targetBlockRead3
        lblName: "sector3:"
        lblValue: NFCReader.targetBlock3
        anchors.top:targetBlockRead2.bottom
        anchors.topMargin: parent.height * 0.02
    }
    InfoTagRow{
        id: targetBlockRead4
        lblName: "sector4"
        lblValue: NFCReader.targetBlock4
        anchors.top:targetBlockRead3.bottom
        anchors.topMargin: parent.height * 0.02
    }
    InfoTagRow{
        id: targetBlockRead5
        lblName: "sector5"
        lblValue: NFCReader.targetBlock5
        anchors.top:targetBlockRead4.bottom
        anchors.topMargin: parent.height * 0.02
    }
    InfoTagRow{
        id: targetBlockRead6
        lblName: "sector6"
        lblValue: NFCReader.targetBlock6
        anchors.top:targetBlockRead5.bottom
        anchors.topMargin: parent.height * 0.02
    }

    TagErrorField{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.10    }

}
