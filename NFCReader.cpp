#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>
#include <QNdefRecord>
#include "NFCReader.h"
#include <QDateTime>
#include <QTimeZone>
#include <QThread>

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

  ,m_lastInteracted {}
  ,m_writeCoordinates {true}
  ,m_readonce {0}
  ,m_doYouWantToReset {false}

{
    m_isNFCSupported = nfcRead->isSupported();
    emit isNFCSupportedChanged();

    scanNFCAvailability();
    connect(nfcAvailableTimer,SIGNAL(timeout()),this,SLOT(scanNFCAvailability()));
    nfcAvailableTimer->start(nfcScanAvailableTimerDuration);

    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::infoTag);
    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::setLastInteracted);
    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::writeTimeToTag);

    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::targetDetected);
    connect(nfcRead,&QNearFieldManager::targetLost,this,&NFCReader::targetLost);

    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::writeCoordinatesLL);



    connect(nfcRead,&QNearFieldManager::targetDetected,this,&NFCReader::setReadCoordinates);

   // connect(m_resetflag,&NFCReader::targetResetedChanged,this,&NFCReader::abc);

    //Q_PROPERTY(bool doYouWantToReset READ doYouWantToReset WRITE setBlocksToZero NOTIFY targetResetedChanged)
   // connect(nfcRead,&QNearFieldManager::;

    //connect(&NFCReader,NFCReader::latitudeFromUserChanged,[](const double &latitudeFromUser);

    //connect(nfcRead, &QNearFieldTarget::ndefMessageRead, this, &NFCReader::readNdefMessages);
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
bool NFCReader::doHaveNdefMessage() const             { return m_doHaveNdefMessage;      }
QString NFCReader::readNdefMessagesSend() const       { return m_readNdefMessage;        }
QString NFCReader::lastInteracted() const             { return m_lastInteracted;         }
//read coordinates
double NFCReader::readCoordinatesLatitude() const     { return m_latitude;               }
double NFCReader::readCoordinatesLongitude() const    { return m_longitude;              }
double NFCReader::latitudeFromUser() const            { return m_latitude;               }
double NFCReader::longitudeFromUser() const           { return m_longitude;              }
//bool   NFCReader::doYouWantToReset() const          {return m_doYouWantToReset;        }


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
   // connect(target,&QNearFieldTarget::~QNearFieldTarget,this,NFCReader::setBlocksToZero);
    m_targetError = "";
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
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+4));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock2(response.toHex(' '));
    setTargetBlockAsString2(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged2();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+8));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock3(response.toHex(' '));
    setTargetBlockAsString3(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged3();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+12));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock4(response.toHex(' '));
    setTargetBlockAsString4(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged4();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+16));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock5(response.toHex(' '));
    setTargetBlockAsString5(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged5();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+20));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock6(response.toHex(' '));
    setTargetBlockAsString6(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged6();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+24));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock7(response.toHex(' '));
    setTargetBlockAsString7(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged7();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+28));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock8(response.toHex(' '));
    setTargetBlockAsString8(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged8();
        }

    m_request = target->sendCommand(readCommand(baseblocknumber+32));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock9(response.toHex(' '));
    setTargetBlockAsString9(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged9();

        }

    m_request = target->sendCommand(readCommand(baseblocknumber+36));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock10(response.toHex(' '));
    setTargetBlockAsString10(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged10();

        }

    m_request = target->sendCommand(readCommand(baseblocknumber+40));
    if(m_request.isValid())
        {
    response = target->requestResponse(m_request).toByteArray();
    setTargetBlock11(response.toHex(' '));
    setTargetBlockAsString11(QString::fromStdString(response.toStdString()));
    emit targetBlockChanged11();

        }

    target->readNdefMessages();

}
void NFCReader::infoTag(QNearFieldTarget *target)
    {
    QByteArray uid(target->uid());

    setTargetUID(uid.toHex(' ').toUpper());
    setTargetAccessMethod(target->accessMethods());
    setTargetType(target->type());

    m_targetConnected = true;
    emit targetConnectedChanged();
    setreadonce(1);
    }

QByteArray NFCReader::readCommand(int blocknumber)
    {
    QByteArray readcmd;

    readcmd.append('\x30');         //read ins
    readcmd.append(blocknumber);    //starting block

      // emit targetBlockChanged();
    return readcmd;
}

void NFCReader::setTargetUID(QByteArray targetUID)
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


    for (const QNdefRecord &record : msg){
        if (record.isRecordType<QNdefNfcTextRecord>()){
           QNdefNfcTextRecord textRecord(record);
           qDebug() << textRecord.text();
           m_readNdefMessage = textRecord.text();
           emit readNdefMessagesChanged();
        }
    }
}

/*void NFCReader::abc(bool *flag)
{

}*/

void NFCReader::setreadonce(int readonce)
{
    if(m_readonce == readonce) return;
    m_readonce = readonce;
    emit readoncechanged();
}

void NFCReader::writeTimeToTag(QNearFieldTarget *target)
{
    QNearFieldTarget::RequestId m_request;
    QByteArray response;


    qint64 secs = QDateTime::currentSecsSinceEpoch();

    int timeAsInt = static_cast<int>(secs);


    int temp = timeAsInt / 1000000000;
    int digit1 = temp % 10;

    temp = timeAsInt /  100000000;
    int digit2 = temp % 10;

    temp = timeAsInt / 10000000;
    int digit3 = temp % 10;

    temp = timeAsInt / 1000000;
    int digit4 = temp % 10;

    temp = timeAsInt / 100000;
    int digit5 = temp % 10;

    temp = timeAsInt / 10000;
    int digit6 = temp % 10;

    temp = timeAsInt / 1000;
    int digit7 = temp % 10;

    temp = timeAsInt / 100;
    int digit8 = temp % 10;

    temp = timeAsInt / 10;
    int digit9 = temp % 10;

    temp = timeAsInt / 1;
    int digit10 = temp % 10;


    QByteArray writeCmd;
    writeCmd.append(0xA2);      //yazma komutu  //10basamak
    writeCmd.append(0x10);         //block number
    writeCmd.append(digit1);
    writeCmd.append(digit2);
    writeCmd.append(digit3);
    writeCmd.append(digit4);


    m_request = target->sendCommand(writeCmd);


    writeCmd={};
    writeCmd.append(0xA2);      //yazma komutu
    writeCmd.append(0x11);         //block number

    writeCmd.append(digit5);
    writeCmd.append(digit6);
    writeCmd.append(digit7);
    writeCmd.append(digit8);
    m_request = target->sendCommand(writeCmd);
    if(m_request.isValid())
    response = target->requestResponse(m_request).toByteArray();

    writeCmd = {};
    writeCmd.append(0xA2);      //yazma komutu
    writeCmd.append(0x12);         //block number

    writeCmd.append(digit9);
    writeCmd.append(digit10);
    writeCmd.append('\x00');
    writeCmd.append('\x00');
    m_request = target->sendCommand(writeCmd);
    if(m_request.isValid())
    response = target->requestResponse(m_request).toByteArray();



}

void NFCReader::setLastInteracted(QNearFieldTarget *target)
{
   // Q_UNUSED (str);
    QByteArray readTimeCmd{};
    QByteArray timeAsEpoch{};
    QNearFieldTarget::RequestId m_request;
    QString timeAsEpochStr = {};

    readTimeCmd.append(0x30);  //readcommand for ntag 2
    readTimeCmd.append(0x10);  // block number for read time
    //readTimeCmd.append(0x0A);  // read 10 bytes

    m_request = target-> sendCommand(readTimeCmd);
    if(m_request.isValid())
    timeAsEpoch = ((target->requestResponse(m_request)).toByteArray()).toHex();
    qDebug() << "epoch as hex : " <<timeAsEpoch;
    for(int i=1; i<=19;i=i+2)
    {
     timeAsEpochStr[i-1] = timeAsEpoch[i];
    }

    timeAsEpochStr.replace(" ", "");
    qint64 epochToConvert = timeAsEpochStr.toLongLong();
    QDateTime time = QDateTime::fromSecsSinceEpoch(epochToConvert);
    QString timeAsString = time.toString();
    qDebug() << "the time str: " << timeAsString;


    m_lastInteracted = timeAsString;
    emit lastInteractedChanged();




}
void NFCReader::writeCoordinatesLL(QNearFieldTarget *target)
{

    QNearFieldTarget::RequestId m_request;
    QByteArray response;   //39.7467642743964, 30.473992072552356
    double longitude = 30.473992;
    double latitude = 39.746764;

    int longitudeToSend = longitude * 1e6;
    int latitudeToSend= latitude * 1e6;
    QByteArray writeCmd;

    int temp = longitudeToSend / 1000000;
    int long1 = temp % 100;

    temp = longitudeToSend     / 10000;
    int long2 = temp % 100;

    temp = longitudeToSend     / 100;
    int long3 = temp % 100;

    temp = longitudeToSend     / 1;
    int long4 = temp % 100;


    //-------------------------------------------
    temp = latitudeToSend / 1000000;
    int lat1 = temp % 100;

    temp = latitudeToSend / 10000;
    int lat2 = temp % 100;

    temp = latitudeToSend / 100;
    int lat3 = temp % 100;

    temp = latitudeToSend / 1;
    int lat4 = temp % 100;

    writeCmd.append(0xA2);
    writeCmd.append(0x14);
    writeCmd.append(long1);
    writeCmd.append(long2);
    writeCmd.append(long3);
    writeCmd.append(long4);


    m_request = target->sendCommand(writeCmd);

    if(m_request.isValid())
    response = target->requestResponse(m_request).toByteArray();

    writeCmd={};

    writeCmd.append(0xA2);
    writeCmd.append(0x15);
    writeCmd.append(lat1);
    writeCmd.append(lat2);
    writeCmd.append(lat3);
    writeCmd.append(lat4);


    m_request = target->sendCommand(writeCmd);
    if(m_request.isValid())
    response = target->requestResponse(m_request).toByteArray();

}
void NFCReader::setReadCoordinates(QNearFieldTarget *target)
{
    QByteArray readCoorCmd{};
    QByteArray latitude{};
    QByteArray longitude{};
    QNearFieldTarget::RequestId m_request{};
    QByteArray coordinatesAsHex{};
    QString temp;



    readCoorCmd.append(0x30);  //readcommand for ntag 2
    readCoorCmd.append(0x14);  // block number for read coordinates

    m_request = target-> sendCommand(readCoorCmd);
    if(m_request.isValid())
        coordinatesAsHex = (target->requestResponse(m_request).toByteArray());
    qDebug() << "coordinates as hex " << coordinatesAsHex;

    double latitude1 = static_cast<quint8>(coordinatesAsHex[0]); //decoding from hex
    double latitude2 = static_cast<quint8>(coordinatesAsHex[1]);
    double  latitude3 = static_cast<quint8>(coordinatesAsHex[2]);
    double latitude4 = static_cast<quint8>(coordinatesAsHex[3]);
    double longitude1 = static_cast<quint8>(coordinatesAsHex[4]);
    double  longitude2 = static_cast<quint8>(coordinatesAsHex[5]);
    double longitude3 = static_cast<quint8>(coordinatesAsHex[6]);
    double longitude4 = static_cast<quint8>(coordinatesAsHex[7]);

    double latitudeDouble = latitude1*1000000+latitude2*10000+latitude3*100+latitude4;
    double longitudeDouble = longitude1*1000000+longitude2*10000+longitude3*100+longitude4;

    qDebug() << "latitude : " << latitudeDouble;
    qDebug() << "longitude : " << longitudeDouble;

    double latitudeReal = longitudeDouble/1e6;
    double longitudeReal = latitudeDouble/1e6;

    m_latitude = latitudeReal;
    emit coordinateLatitudeChanged();
    m_longitude = longitudeReal;
    emit coordinateLongitudeChanged();

}
void NFCReader::setLatitudeFromUser(const QString &latitudeFromUser)
{
    double latitudeFromUserD = latitudeFromUser.toDouble();

    if(m_latitude == latitudeFromUserD) return;
    m_latitude = latitudeFromUserD;
    emit latitudeFromUserChanged();
    qDebug()<<"latitudefromuser"<< latitudeFromUserD;
    qDebug()<<"m_latitude"<< m_latitude;

}
void NFCReader::setLongitudeFromUser(const QString &longitudeFromUser)
{
    double longitudeFromUserDouble = longitudeFromUser.toDouble();

    if(m_longitude == longitudeFromUserDouble) return;
    m_longitude = longitudeFromUserDouble;
    emit longitudeFromUserChanged();
    qDebug()<<"latitudefromuser"<< longitudeFromUserDouble;
    qDebug()<<"m_latitude"<< m_longitude;

}
/*
void NFCReader::setBlocksToZero(const bool doYouWantToReset, QNearFieldTarget *target)
{

    //doYouWantToReset = getReset();

    QByteArray response;
    qDebug() << "do you want to reset" << doYouWantToReset;
    if(!targetConnected()) return;
    if (!doYouWantToReset) return;
    QByteArray resetCmd;
    QNearFieldTarget::RequestId m_request;
    qDebug() << "do you want to reset2" << doYouWantToReset;
    for(int i=0 ; i<=baseblocknumber+36 ; i++)
    {
        qDebug() << "do you want to reset3" << doYouWantToReset;
        resetCmd.append(0xA2);
        resetCmd.append(baseblocknumber + i);
        resetCmd.append('\x00');
        resetCmd.append('\x00');
        resetCmd.append('\x00');
        resetCmd.append('\x00');
        qDebug() << "message to send is " << resetCmd;
        qDebug() << "do you want to reset4" << doYouWantToReset;
        m_request = target->sendCommand(resetCmd);
        qDebug() << "do you want to reset5" << doYouWantToReset;
       if(m_request.isValid())
       {
           qDebug() << "do you want to reset6" << doYouWantToReset;
       response = target->requestResponse(m_request).toByteArray();
       qDebug()<< "response" <<response;
       }
       QThread::msleep(10);

        qDebug() << "do you want to reset7" << doYouWantToReset;
    }
    emit targetResetedChanged();
    //doYouWantToReset = false;


}






void NFCReader::setReset(bool resetflag)
{
    m_resetflag = resetflag;
    emit targetResetedChanged();
}
bool NFCReader::getReset()
{
    return m_resetflag;
}

*/













