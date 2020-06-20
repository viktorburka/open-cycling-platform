#ifndef PHONECOMMUNICATION_H
#define PHONECOMMUNICATION_H

#include <QObject>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothLocalDevice>

class QBluetoothAddress;
class QBluetoothServiceInfo;

class PhoneCommunication : public QObject
{
    Q_OBJECT
public:
    enum State {
        Initial,
        DeviceDiscovery,
        Pairing,
        ServiceDiscovery,
        SocketConnect,
        Error,
        Connected
    };

    PhoneCommunication(QObject *parent = nullptr);
    void connect();

signals:
    void connected();
    void error(const QString &);
    void stateChanged(State state);

private slots:
    void serviceConnected();
    void serviceError(QBluetoothSocket::SocketError);
    void svcDiscoveryDone();
    void devDiscoveryDone();
    void showDiscoveredDevice(const QBluetoothDeviceInfo &);
    void showDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error);
    void processPairingFinished(const QBluetoothAddress &, QBluetoothLocalDevice::Pairing);

private:
    bool inProgress() const;
    void connectToPhone(const QBluetoothAddress & addr);
    void emitError(const QString & err);
    void emitConnected();
    void changeState(State state);
    void discoverAndTryAgain();
    QString stateToString(State state) const;

    bool m_active;
    State m_state;
    QBluetoothSocket* m_socket;
    QBluetoothLocalDevice* m_bluetooth;
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscovery;
    QBluetoothServiceDiscoveryAgent* m_serviceDiscovery;
};

#endif // PHONECOMMUNICATION_H
