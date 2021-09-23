#ifndef NFCREADER_H
#define NFCREADER_H

#include <QObject>
#include <QNearFieldManager>
#include <QNearFieldTarget>
#include <QTimer>

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
    Q_PROPERTY(QByteArray targetBlock READ targetBlock NOTIFY targetBlockChanged)
    Q_PROPERTY(QByteArray targetBlock2 READ targetBlock2 NOTIFY targetBlockChanged2)
    Q_PROPERTY(QByteArray targetBlock3 READ targetBlock3 NOTIFY targetBlockChanged3)
    Q_PROPERTY(QByteArray targetBlock4 READ targetBlock4 NOTIFY targetBlockChanged4)
    Q_PROPERTY(QByteArray targetBlock5 READ targetBlock5 NOTIFY targetBlockChanged5)
    Q_PROPERTY(QByteArray targetBlock6 READ targetBlock6 NOTIFY targetBlockChanged6)

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
    QNdefMessage ndefMessage() const;
    // block okuma için deneme
    QByteArray targetBlock() const;
    QByteArray targetBlock2() const;
    QByteArray targetBlock3() const;
    QByteArray targetBlock4() const;
    QByteArray targetBlock5() const;
    QByteArray targetBlock6() const;

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
    QByteArray m_targetBlock2;
    QByteArray m_targetBlock3;
    QByteArray m_targetBlock4;
    QByteArray m_targetBlock5;
    QByteArray m_targetBlock6;
    QByteArray m_targetBlock;

    QTimer *nfcAvailableTimer = new QTimer();

};

#endif // NFCREADER_H
