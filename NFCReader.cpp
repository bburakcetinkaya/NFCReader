#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>
#include <QNdefRecord>
#include "NFCReader.h"

//static const QByteArray key_A = "FF 88 00 02 60 D3 F7 D3 F7 D3 F7";
static const int nfcScanAvailableTimerDuration = 2000;
static const char baseblocknumber = 4;

NFCReader::NFCReader(QObject *parent) : QObject(parent)
  ,m_isNFCSupported {false}
  ,m_isNFCAvailable {false}
  ,m_supportedMessage {"NFC is not supported in this device"}
  ,m_nfcNotAvailable {"Please enable your NFC"}
  ,m_targetDetectingMessage {"Move target to the device"}
  ,m_targetDetecting {false}
  ,m_targetConnected {false}
  ,m_targetUID {""}
  ,m_targetAccessMethod {""}
  ,m_targetType {""}
  ,m_targetError {""}
  ,m_targetBlock  {"Could not read"}
  ,m_targetBlock2 {"Could not read"}
  ,m_targetBlock3 {"Could not read"}
  ,m_targetBlock4 {"Could not read"}
  ,m_targetBlock5 {"Could not read"}
  ,m_targetBlock6 {"Could not read"}
  ,m_targetBlock7 {"Could not read"}
  ,m_targetBlock8 {"Could not read"}
  ,m_targetBlock9 {"Could not read"}
  ,m_targetBlock10{"Could not read"}
  ,m_targetBlock11 {"Could not read"}

  ,m_targetBlockAsString{"Could not read"}
  //ndef message read
  ,m_doHaveNdefMessage {false}
  ,m_readNdefMessage {}

  ,m_readonce {0}

{
    m_isNFCSupported = nfcRead->isSupported();
    emit isNFCSupportedChanged();

    scanNFCAvailability();

    connect(nfcAvailableTimer,SIGNAL(timeout()),this,SLOT(scanNFCAvailability()));
    nfcAvailableTimer->start(nfcScanAvailableTimerDuration);

    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::infoTag);
    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::targetDetected);
    connect(nfcRead,&QNearFieldManager::targetLost,this,&NFCReader::targetLost);

  //  connect(nfcRead, &QNearFieldTarget::ndefMessageRead, this, &NFCReader::ndefMessageRead);
  //  Q_PROPERTY(int number READ setreadonce WRITE setreadonce NOTIFY readoncechanged)
    //connect(sender, SIGNAL(destroyed()), this, SLOT(objectDestroyed(QObject*)));
    //connect(number, SIGNAL(setreadonceqml),this,&NFCReader::setreadonce);

    }

bool NFCReader::isNFCSupported() const           { return m_isNFCSupported;     }
bool NFCReader::isNFCAvailable() const           { return m_isNFCAvailable;     }
bool NFCReader::targetDetecting() const          { return m_targetDetecting;    }
bool NFCReader::targetConnected() const          { return m_targetConnected;    }
QByteArray NFCReader::targetUID() const          { return m_targetUID;          }
QString NFCReader::targetAccessMethod() const    { return m_targetAccessMethod; }
QString NFCReader::targetType() const            { return m_targetType;         }
QString NFCReader::targetError() const           { return m_targetError;        }
 // QNdefMessage NFCReader::ndefMessage() const      { return QNdefMessage(txtRecord)}
//  lazım olunca düzenle
//block read için deneme
QByteArray NFCReader::targetBlock() const         { return m_targetBlock;         }
QByteArray NFCReader::targetBlock2() const        { return m_targetBlock2;        }
QByteArray NFCReader::targetBlock3() const        { return m_targetBlock3;        }
QByteArray NFCReader::targetBlock4() const        { return m_targetBlock4;        }
QByteArray NFCReader::targetBlock5() const        { return m_targetBlock5;        }
QByteArray NFCReader::targetBlock6() const        { return m_targetBlock6;        }
QByteArray NFCReader::targetBlock7() const        { return m_targetBlock7;        }
QByteArray NFCReader::targetBlock8() const        { return m_targetBlock8;        }
QByteArray NFCReader::targetBlock9() const        { return m_targetBlock9;        }
QByteArray NFCReader::targetBlock10() const        { return m_targetBlock10;        }
QByteArray NFCReader::targetBlock11() const        { return m_targetBlock11;        }
//ekran arası geçişler için
int NFCReader::readonce() const                   { return m_readonce;            }
//blocklar string olarak
QString NFCReader::targetBlockAsString() const        { return m_targetBlockAsString;    }
QString NFCReader::targetBlockAsString2() const       { return m_targetBlockAsString2;   }
QString NFCReader::targetBlockAsString3() const       { return m_targetBlockAsString3;   }
QString NFCReader::targetBlockAsString4() const       { return m_targetBlockAsString4;   }
QString NFCReader::targetBlockAsString5() const       { return m_targetBlockAsString5;   }
QString NFCReader::targetBlockAsString6() const       { return m_targetBlockAsString6;   }
QString NFCReader::targetBlockAsString7() const       { return m_targetBlockAsString7;   }
QString NFCReader::targetBlockAsString8() const       { return m_targetBlockAsString8;   }
QString NFCReader::targetBlockAsString9() const       { return m_targetBlockAsString9;   }
QString NFCReader::targetBlockAsString10() const      { return m_targetBlockAsString10;  }
QString NFCReader::targetBlockAsString11() const      { return m_targetBlockAsString11;  }
//ndef message falan okuma
bool NFCReader::doHaveNdefMessage() const             { return m_doHaveNdefMessage;    }
QString NFCReader::readNdefMessagesSend() const           { return m_readNdefMessage;       }

void NFCReader::setNFCAvailable(bool isNFCAvailable)
    {
    m_isNFCAvailable = isNFCAvailable;
    emit isNFCAvailableChanged();
    }

void NFCReader::scanNFCAvailability()
    {
    setNFCAvailable(nfcRead->isAvailable());
    if(isNFCAvailable())
        {
        nfcRead->startTargetDetection();
        m_targetDetecting = true;
        emit targetDetectingChanged();
        }
    else
        {
        nfcRead->setTargetAccessModes(QNearFieldManager::NoTargetAccess);
        nfcRead->stopTargetDetection();
        m_targetDetecting = false;
        emit targetDetectingChanged();
        }
    }

void NFCReader::targetDetected(QNearFieldTarget *target)
    {
    QByteArray response;
   // QString targetBlockasString;
    connect(target,&QNearFieldTarget::requestCompleted,this,&NFCReader::readRequest);
    connect(target,&QNearFieldTarget::error,this,&NFCReader::setTargetError);
    connect(target,&QNearFieldTarget::ndefMessageRead, this, &NFCReader::readNdefMessages);
    m_targetError = "";
    qDebug()<<"has ndef message: " << target->hasNdefMessage();
    if(target->hasNdefMessage()){
        m_doHaveNdefMessage = true;
        emit doHaveNdefMessageChanged();
    }
    m_request = target->sendCommand(readCommand(baseblocknumber));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock(response.toHex(' '));
    setTargetBlockAsString(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+4));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock2(response.toHex(' '));
    setTargetBlockAsString2(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged2();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+8));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock3(response.toHex(' '));
    setTargetBlockAsString3(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged3();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+12));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock4(response.toHex(' '));
    setTargetBlockAsString4(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged4();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+16));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock5(response.toHex(' '));
    setTargetBlockAsString5(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged5();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+20));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock6(response.toHex(' '));
    setTargetBlockAsString6(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged6();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+24));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock7(response.toHex(' '));
    setTargetBlockAsString7(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged7();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+28));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock8(response.toHex(' '));
    setTargetBlockAsString8(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged8();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+32));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock9(response.toHex(' '));
    setTargetBlockAsString9(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged9();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+36));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock10(response.toHex(' '));
    setTargetBlockAsString10(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged10();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+40));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock11(response.toHex(' '));
    setTargetBlockAsString11(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged11();
    qDebug() << response;
        }

    //read ndef part
    m_request = target->readNdefMessages();
  //  response = target->sendCommand(m_request);


}
void NFCReader::infoTag(QNearFieldTarget *target)
    {
    QByteArray uid(target->uid());

    setTargetUID(uid.toHex(' ').toUpper());
    setTargetAccessMethod(target->accessMethods());
    setTargetType(target->type());

    m_targetConnected = true;
    qDebug() <<"in infotag ---> "<< m_targetBlock;
    emit targetConnectedChanged();
    setreadonce(1);
    }

QByteArray NFCReader::readCommand(int blocknumber)
    {
    QByteArray readcmd;

    readcmd.append('\x30');         //read ins
    readcmd.append(blocknumber);    //starting block
                                    // 4 blocks to read

      // emit targetBlockChanged();
    return readcmd;
}

void NFCReader::setTargetUID(QByteArray targetUID)//rld\xFET\x02""12asfgg\xFE\x00\x00
    {
    if(m_targetUID == targetUID)    return;
    else m_targetUID = targetUID;
    emit targetUIDChanged();
    }

void NFCReader::setTargetType(QNearFieldTarget::Type typeTarget)
    {
    switch (typeTarget)
       {

    case QNearFieldTarget::ProprietaryTag:
         m_targetType = "NFC TAG TYPE 5 ";
         break;
    case QNearFieldTarget::NfcTagType1:
         m_targetType = "NFC TAG TYPE 1 ";
         break;
    case QNearFieldTarget::NfcTagType2:
         m_targetType = "NFC TAG TYPE 2 ";
         break;
    case QNearFieldTarget::NfcTagType3:
         m_targetType = "NFC TAG TYPE 3 ";
         break;
    case QNearFieldTarget::NfcTagType4:
         m_targetType = "NFC TAG TYPE 4 ";
         break;
    case QNearFieldTarget::MifareTag:
         m_targetType = "Mifare target";
         break;
    default:
         m_targetType = "undefined";
         break;
        }

    emit targetTypeChanged();

    }

void NFCReader::setTargetAccessMethod(QNearFieldTarget::AccessMethods accessMethod)
    {
    switch (accessMethod)
        {

     case QNearFieldTarget::UnknownAccess:
          m_targetAccessMethod = "The target supports an unknown access type.";
          break;
     case QNearFieldTarget::NdefAccess:
          m_targetAccessMethod = "The target supports NDEF messages using readNdefMessages() and writeNdefMessages().";
          break;
     case QNearFieldTarget::TagTypeSpecificAccess:
          m_targetAccessMethod = "The target supports sending tag type specific commands using sendCommand() and sendCommands().";
          break;
     case QNearFieldTarget::LlcpAccess:
          m_targetAccessMethod = "The target supports peer-to-peer LLCP communication.";
          break;
     case QNearFieldTarget::NdefAccess |  QNearFieldTarget::TagTypeSpecificAccess:
          m_targetAccessMethod = "NdefAccess & TagTypeSpecifAccess";
          break;
    default:
          m_targetAccessMethod = "AccessMethod unefined";
          break;
         }

    emit targetAccessMethodChanged();
    }

void NFCReader::setTargetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id)
    {
    Q_UNUSED(error);
    Q_UNUSED(id);

    switch (error)
          {
        case QNearFieldTarget::NoError:
            m_targetError = "";
            break;
        case QNearFieldTarget::UnsupportedError:
            m_targetError = "Unsupported tag";
            break;
        case QNearFieldTarget::TargetOutOfRangeError:
            m_targetError = "Tag removed from field";
            break;
        case QNearFieldTarget::NoResponseError:
            m_targetError = "No response from tag";
            break;
        case QNearFieldTarget::ChecksumMismatchError:
            m_targetError = "Checksum mismatch";
            break;
        case QNearFieldTarget::InvalidParametersError:
            m_targetError = "Invalid parameters";
            break;
        case QNearFieldTarget::NdefReadError:
            m_targetError = "NDEF read error";
            break;
        case QNearFieldTarget::NdefWriteError:
            m_targetError = "NDEF write error";
            break;
        case QNearFieldTarget::CommandError:
            m_targetError = "Failed to send a command to the target.";
            break;
        default:
            m_targetError = "Unknown error";
          }

        emit targetErrorChanged();
    }

void NFCReader::readRequest(const QNearFieldTarget::RequestId &id)
    {
    Q_UNUSED(id)
    }

void NFCReader::targetLost(QNearFieldTarget *target)
    {
    m_targetConnected = false;
    emit targetConnectedChanged();

   // setTargetUID("");
    target->deleteLater();
    }

void NFCReader::setTargetBlock(QByteArray array)
    {
    if (m_targetBlock == array) return;
            m_targetBlock = array;
            emit targetBlockChanged();

    }
void NFCReader::setTargetBlock2(QByteArray array)
    {
    if (m_targetBlock2 == array) return;
            m_targetBlock2 = array;
            emit targetBlockChanged2();

    }
void NFCReader::setTargetBlock3(QByteArray array)
    {
    if (m_targetBlock3 == array) return;
            m_targetBlock3 = array;
            emit targetBlockChanged3();

    }
void NFCReader::setTargetBlock4(QByteArray array)
    {
    if (m_targetBlock4 == array) return;
            m_targetBlock4 = array;
            emit targetBlockChanged4();

    }
void NFCReader::setTargetBlock5(QByteArray array)
    {
    if (m_targetBlock5 == array) return;
            m_targetBlock5 = array;
            emit targetBlockChanged5();

    }
void NFCReader::setTargetBlock6(QByteArray array)
    {
    if (m_targetBlock6 == array) return;
            m_targetBlock6 = array;
            emit targetBlockChanged6();

    }
void NFCReader::setTargetBlock7(QByteArray array)
    {
    if (m_targetBlock7 == array) return;
            m_targetBlock7 = array;
            emit targetBlockChanged7();

    }
void NFCReader::setTargetBlock8(QByteArray array)
    {
    if (m_targetBlock8 == array) return;
            m_targetBlock8 = array;
            emit targetBlockChanged8();

    }
void NFCReader::setTargetBlock9(QByteArray array)
    {
    if (m_targetBlock9 == array) return;
            m_targetBlock9 = array;
            emit targetBlockChanged9();

    }
void NFCReader::setTargetBlock10(QByteArray array)
    {
    if (m_targetBlock10 == array) return;
            m_targetBlock10 = array;
            emit targetBlockChanged10();

    }
void NFCReader::setTargetBlock11(QByteArray array)
    {
    if (m_targetBlock11 == array) return;
            m_targetBlock11 = array;
            emit targetBlockChanged11();

    }
// blockları string yapma kısmı
void NFCReader::setTargetBlockAsString(QString str)
{
    if (m_targetBlockAsString == str) return;
    m_targetBlockAsString = str;
    emit targetBlockAsStringChanged();

}
void NFCReader::setTargetBlockAsString2(QString str)
{
    if (m_targetBlockAsString2 == str) return;
    m_targetBlockAsString2 = str;
    emit targetBlockAsStringChanged2();

}
void NFCReader::setTargetBlockAsString3(QString str)
{
    if (m_targetBlockAsString3 == str) return;
    m_targetBlockAsString3 = str;
    emit targetBlockAsStringChanged3();

}
void NFCReader::setTargetBlockAsString4(QString str)
{
    if (m_targetBlockAsString4 == str) return;
    m_targetBlockAsString4 = str;
    emit targetBlockAsStringChanged4();

}
void NFCReader::setTargetBlockAsString5(QString str)
{
    if (m_targetBlockAsString5 == str) return;
    m_targetBlockAsString5 = str;
    emit targetBlockAsStringChanged5();

}
void NFCReader::setTargetBlockAsString6(QString str)
{
    if (m_targetBlockAsString6 == str) return;
    m_targetBlockAsString6 = str;
    emit targetBlockAsStringChanged6();

}
void NFCReader::setTargetBlockAsString7(QString str)
{
    if (m_targetBlockAsString7 == str) return;
    m_targetBlockAsString7 = str;
    emit targetBlockAsStringChanged7();

}
void NFCReader::setTargetBlockAsString8(QString str)
{
    if (m_targetBlockAsString8 == str) return;
    m_targetBlockAsString8 = str;
    emit targetBlockAsStringChanged8();

}
void NFCReader::setTargetBlockAsString9(QString str)
{
    if (m_targetBlockAsString9 == str) return;
    m_targetBlockAsString9 = str;
    emit targetBlockAsStringChanged9();

}void NFCReader::setTargetBlockAsString10(QString str)
{
    if (m_targetBlockAsString10 == str) return;
    m_targetBlockAsString10 = str;
    emit targetBlockAsStringChanged10();

}
void NFCReader::setTargetBlockAsString11(QString str)
{
    if (m_targetBlockAsString11 == str) return;
    m_targetBlockAsString11 = str;
    emit targetBlockAsStringChanged11();

}
void NFCReader::readNdefMessages(const QNdefMessage &msg)
{
    /*A QNdefMessage is a collection of 0 or more QNdefRecords.
     * QNdefMessage inherits from QList<QNdefRecord> and
     * therefore the standard QList functions can be used to manipulate
     * the NDEF records in the message.*/

    for (const QNdefRecord &record : msg){
        if (record.isRecordType<QNdefNfcTextRecord>()){
           QNdefNfcTextRecord textRecord(record);
           qDebug() << textRecord.text();
           m_readNdefMessage = textRecord.text();
           emit readNdefMessagesChanged();
        }
    }
}

void NFCReader::setreadonce(int readonce)
{
    if(m_readonce == readonce) return;
    m_readonce = readonce;
    qDebug() << "readonce:   " << readonce;
    qDebug() << "m_readonce: " << m_readonce;
    emit readoncechanged();
}
























