#ifndef NFCREADER_H
#define NFCREADER_H

#include <QObject>
#include <QNearFieldManager>
#include <QNearFieldTarget>
#include <QString>
#include <QTimer>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>



class NFCReader : public QObject
{
 Q_OBJECT
    Q_PROPERTY(bool isNFCSupported READ isNFCSupported NOTIFY isNFCSupportedChanged)
    Q_PROPERTY(bool isNFCAvailable READ isNFCAvailable WRITE setNFCAvailable NOTIFY isNFCAvailableChanged)
    Q_PROPERTY(bool targetDetecting READ targetDetecting NOTIFY targetDetectingChanged)
    Q_PROPERTY(bool targetConnected READ targetConnected NOTIFY targetConnectedChanged)
    Q_PROPERTY(QString supportedMessage MEMBER m_supportedMessage CONSTANT)
    Q_PROPERTY(QString nfcNotAvailableMessage MEMBER m_nfcNotAvailable CONSTANT)
    Q_PROPERTY(QString targetDetectingMessage MEMBER m_targetDetectingMessage CONSTANT)
    Q_PROPERTY(QString targetAccessMethod READ targetAccessMethod NOTIFY targetAccessMethodChanged)
    Q_PROPERTY(QString targetType READ targetType NOTIFY targetTypeChanged)
    Q_PROPERTY(QString targetError READ targetError NOTIFY targetErrorChanged)
    Q_PROPERTY(QByteArray targetUID READ targetUID NOTIFY targetUIDChanged)
    //ndef message read kısmı
    Q_PROPERTY(bool doHaveNdefMessage READ doHaveNdefMessage NOTIFY doHaveNdefMessageChanged)
    Q_PROPERTY(QString readNdefMessagesSend READ readNdefMessagesSend NOTIFY readNdefMessagesChanged)
    //block read kısmı
    Q_PROPERTY(QByteArray targetBlock READ targetBlock NOTIFY targetBlockChanged)
    Q_PROPERTY(QByteArray targetBlock2 READ targetBlock2 NOTIFY targetBlockChanged2)
    Q_PROPERTY(QByteArray targetBlock3 READ targetBlock3 NOTIFY targetBlockChanged3)
    Q_PROPERTY(QByteArray targetBlock4 READ targetBlock4 NOTIFY targetBlockChanged4)
    Q_PROPERTY(QByteArray targetBlock5 READ targetBlock5 NOTIFY targetBlockChanged5)
    Q_PROPERTY(QByteArray targetBlock6 READ targetBlock6 NOTIFY targetBlockChanged6)
    Q_PROPERTY(QByteArray targetBlock7 READ targetBlock7 NOTIFY targetBlockChanged7)
    Q_PROPERTY(QByteArray targetBlock8 READ targetBlock8 NOTIFY targetBlockChanged8)
    Q_PROPERTY(QByteArray targetBlock9 READ targetBlock9 NOTIFY targetBlockChanged9)
    Q_PROPERTY(QByteArray targetBlock10 READ targetBlock10 NOTIFY targetBlockChanged10)
    Q_PROPERTY(QByteArray targetBlock11 READ targetBlock11 NOTIFY targetBlockChanged11)
    //blocklar string olarak
    Q_PROPERTY(QString targetBlockAsString READ targetBlockAsString NOTIFY targetBlockAsStringChanged)
    Q_PROPERTY(QString targetBlockAsString2 READ targetBlockAsString2 NOTIFY targetBlockAsStringChanged2)
    Q_PROPERTY(QString targetBlockAsString3 READ targetBlockAsString3 NOTIFY targetBlockAsStringChanged3)
    Q_PROPERTY(QString targetBlockAsString4 READ targetBlockAsString4 NOTIFY targetBlockAsStringChanged4)
    Q_PROPERTY(QString targetBlockAsString5 READ targetBlockAsString5 NOTIFY targetBlockAsStringChanged5)
    Q_PROPERTY(QString targetBlockAsString6 READ targetBlockAsString6 NOTIFY targetBlockAsStringChanged6)
    Q_PROPERTY(QString targetBlockAsString7 READ targetBlockAsString7 NOTIFY targetBlockAsStringChanged7)
    Q_PROPERTY(QString targetBlockAsString8 READ targetBlockAsString8 NOTIFY targetBlockAsStringChanged8)
    Q_PROPERTY(QString targetBlockAsString9 READ targetBlockAsString9 NOTIFY targetBlockAsStringChanged9)
    Q_PROPERTY(QString targetBlockAsString10 READ targetBlockAsString10 NOTIFY targetBlockAsStringChanged10)
    Q_PROPERTY(QString targetBlockAsString11 READ targetBlockAsString11 NOTIFY targetBlockAsStringChanged11)

    Q_PROPERTY(int readonce READ readonce WRITE setreadonce NOTIFY readoncechanged)


    //(item, SIGNAL(qmlSignal(QString)),&myClass, SLOT(cppSlot(QString)));
public:
    explicit NFCReader(QObject *parent = nullptr);
    bool isNFCSupported() const;
    bool isNFCAvailable() const;
    bool targetDetecting() const;
    bool targetConnected() const;
    QString targetAccessMethod() const;
    QString targetType() const;
    QString targetError() const;
    QByteArray targetUID() const;
    // block okuma için deneme
    QByteArray targetBlock() const;
    QByteArray targetBlock2() const;
    QByteArray targetBlock3() const;
    QByteArray targetBlock4() const;
    QByteArray targetBlock5() const;
    QByteArray targetBlock6() const;
    QByteArray targetBlock7() const;
    QByteArray targetBlock8() const;
    QByteArray targetBlock9() const;
    QByteArray targetBlock10() const;
    QByteArray targetBlock11() const;
    // blocklar string olarak
    QString targetBlockAsString() const;
    QString targetBlockAsString2() const;
    QString targetBlockAsString3() const;
    QString targetBlockAsString4() const;
    QString targetBlockAsString5() const;
    QString targetBlockAsString6() const;
    QString targetBlockAsString7() const;
    QString targetBlockAsString8() const;
    QString targetBlockAsString9() const;
    QString targetBlockAsString10() const;
    QString targetBlockAsString11() const;
    // ndef message read
    bool doHaveNdefMessage() const;
    QString readNdefMessagesSend() const;
    int readonce() const;

public slots:
    void setNFCAvailable(bool isNFCAvailable);
    void scanNFCAvailability();
    void targetDetected(QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);

    void setTargetUID(QByteArray targetUID);
    void setTargetType(QNearFieldTarget::Type typeTarget);
    void setTargetAccessMethod(QNearFieldTarget::AccessMethods accessMethod);
    void setTargetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id);

    void infoTag(QNearFieldTarget *target);
    void readRequest(const QNearFieldTarget::RequestId &id);
    // block okuma için deneme
    void setTargetBlock(QByteArray array);
    void setTargetBlock2(QByteArray array);
    void setTargetBlock3(QByteArray array);
    void setTargetBlock4(QByteArray array);
    void setTargetBlock5(QByteArray array);
    void setTargetBlock6(QByteArray array);
    void setTargetBlock7(QByteArray array);
    void setTargetBlock8(QByteArray array);
    void setTargetBlock9(QByteArray array);
    void setTargetBlock10(QByteArray array);
    void setTargetBlock11(QByteArray array);
    // blocklar String olarak
    void setTargetBlockAsString(QString str);
    void setTargetBlockAsString2(QString str);
    void setTargetBlockAsString3(QString str);
    void setTargetBlockAsString4(QString str);
    void setTargetBlockAsString5(QString str);
    void setTargetBlockAsString6(QString str);
    void setTargetBlockAsString7(QString str);
    void setTargetBlockAsString8(QString str);
    void setTargetBlockAsString9(QString str);
    void setTargetBlockAsString10(QString str);
    void setTargetBlockAsString11(QString str);


    //ndefmessage read
    void readNdefMessages(const QNdefMessage &msg);



    void setreadonce(int readonce);
    //devam edilecek

signals:
    void isNFCSupportedChanged();
    void isNFCAvailableChanged();
    void targetDetectingChanged();
    void targetConnectedChanged();
    void targetAccessMethodChanged();
    void targetTypeChanged();
    void targetErrorChanged();
    void targetUIDChanged();
    // block okuma için deneme
    void targetBlockChanged();
    void targetBlockChanged2();
    void targetBlockChanged3();
    void targetBlockChanged4();
    void targetBlockChanged5();
    void targetBlockChanged6();
    void targetBlockChanged7();
    void targetBlockChanged8();
    void targetBlockChanged9();
    void targetBlockChanged10();
    void targetBlockChanged11();
    //blocklar String olarak
    void targetBlockAsStringChanged();
    void targetBlockAsStringChanged2();
    void targetBlockAsStringChanged3();
    void targetBlockAsStringChanged4();
    void targetBlockAsStringChanged5();
    void targetBlockAsStringChanged6();
    void targetBlockAsStringChanged7();
    void targetBlockAsStringChanged8();
    void targetBlockAsStringChanged9();
    void targetBlockAsStringChanged10();
    void targetBlockAsStringChanged11();
    //ndef message readlı falan
    void doHaveNdefMessageChanged();
    void readNdefMessagesChanged();


    void readoncechanged();

private:
    QByteArray readCommand(int blocknumber);
    QNearFieldManager *nfcRead = new QNearFieldManager(this);
    QNearFieldTarget::RequestId m_request;
    bool m_isNFCSupported;
    bool m_isNFCAvailable;
    bool m_targetDetecting;
    bool m_targetConnected;
    QString m_supportedMessage;
    QString m_nfcNotAvailable;
    QString m_targetDetectingMessage;
    QString m_targetAccessMethod;
    QString m_targetType;
    QString m_targetError;
    QByteArray m_targetUID;
    // block okuma için deneme
    QByteArray m_targetBlock;
    QByteArray m_targetBlock2;
    QByteArray m_targetBlock3;
    QByteArray m_targetBlock4;
    QByteArray m_targetBlock5;
    QByteArray m_targetBlock6;
    QByteArray m_targetBlock7;
    QByteArray m_targetBlock8;
    QByteArray m_targetBlock9;
    QByteArray m_targetBlock10;
    QByteArray m_targetBlock11;
    // block stringleri
    QString m_targetBlockAsString;
    QString m_targetBlockAsString2;
    QString m_targetBlockAsString3;
    QString m_targetBlockAsString4;
    QString m_targetBlockAsString5;
    QString m_targetBlockAsString6;
    QString m_targetBlockAsString7;
    QString m_targetBlockAsString8;
    QString m_targetBlockAsString9;
    QString m_targetBlockAsString10;
    QString m_targetBlockAsString11;
    //ndef messages
    bool m_doHaveNdefMessage;
    QString m_readNdefMessage;
    int m_readonce;

    QTimer *nfcAvailableTimer = new QTimer();

};

#endif // NFCREADER_H
