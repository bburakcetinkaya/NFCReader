#include <QDebug>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>
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
  ,m_targetBlock  {"empty"}
  ,m_targetBlock2 {"empty"}
  ,m_targetBlock3 {"empty"}
  ,m_targetBlock4 {"empty"}
  ,m_targetBlock5 {"empty"}
  ,m_targetBlock6 {"empty"}

    {
    m_isNFCSupported = nfcRead->isSupported();
    emit isNFCSupportedChanged();

    scanNFCAvailability();

    connect(nfcAvailableTimer,SIGNAL(timeout()),this,SLOT(scanNFCAvailability()));
    nfcAvailableTimer->start(nfcScanAvailableTimerDuration);

    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::infoTag);
    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::targetDetected);
    connect(nfcRead,&QNearFieldManager::targetLost,this,&NFCReader::targetLost);

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
QByteArray NFCReader::targetBlock() const        { return m_targetBlock;        }
QByteArray NFCReader::targetBlock2() const        { return m_targetBlock2;        }
QByteArray NFCReader::targetBlock3() const        { return m_targetBlock3;        }
QByteArray NFCReader::targetBlock4() const        { return m_targetBlock4;        }
QByteArray NFCReader::targetBlock5() const        { return m_targetBlock5;        }
QByteArray NFCReader::targetBlock6() const        { return m_targetBlock6;        }

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
    QString DataAsString;
    connect(target,&QNearFieldTarget::requestCompleted,this,&NFCReader::readRequest);
    connect(target,&QNearFieldTarget::error,this,&NFCReader::setTargetError);

    m_targetError = "";



    m_request = target->sendCommand(readCommand(baseblocknumber));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock(response.toHex(' '));
    emit targetBlockChanged();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+4));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock2(response.toHex(' '));
    emit targetBlockChanged2();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+8));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock3(response.toHex(' '));
    emit targetBlockChanged3();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+12));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock4(response.toHex(' '));
    emit targetBlockChanged4();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+16));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock5(response.toHex(' '));
    emit targetBlockChanged5();
    qDebug() << response;
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+20));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock6(response.toHex(' '));
    emit targetBlockChanged6();
    qDebug() << response;
        }



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

    setTargetUID("");
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
























