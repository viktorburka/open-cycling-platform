#include "phonecommunication.h"
#include "settings.h"

#include <QBluetoothLocalDevice>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>
#include <QtDebug>

PhoneCommunication::PhoneCommunication(QObject *parent)
    : QObject(parent)
    , m_active(false)
    , m_state(Initial)
{
    m_bluetooth = new QBluetoothLocalDevice(this);
    QObject::connect(m_bluetooth, SIGNAL(pairingFinished(const QBluetoothAddress &, QBluetoothLocalDevice::Pairing)),
            SLOT(processPairingFinished(const QBluetoothAddress &, QBluetoothLocalDevice::Pairing)));

    m_deviceDiscovery = new QBluetoothDeviceDiscoveryAgent(this);
    QObject::connect(m_deviceDiscovery, SIGNAL(finished()), SLOT(devDiscoveryDone()));
    QObject::connect(m_deviceDiscovery, SIGNAL(canceled()), SLOT(devDiscoveryDone()));
    QObject::connect(m_deviceDiscovery, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo &)),
                     SLOT(showDiscoveredDevice(const QBluetoothDeviceInfo &)));
    QObject::connect(m_deviceDiscovery, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
                     SLOT(showDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error)));

    m_serviceDiscovery = new QBluetoothServiceDiscoveryAgent(this);
    QObject::connect(m_serviceDiscovery, SIGNAL(finished()), SLOT(svcDiscoveryDone()));
    QObject::connect(m_serviceDiscovery, SIGNAL(canceled()), SLOT(svcDiscoveryDone()));

    m_socket = new QBluetoothSocket(this);
    QObject::connect(m_socket, SIGNAL(connected()), SLOT(serviceConnected()));
    QObject::connect(m_socket, SIGNAL(error(QBluetoothSocket::SocketError)),
                     SLOT(serviceError(QBluetoothSocket::SocketError)));

    changeState(Initial);
}

void PhoneCommunication::connect()
{
    if (inProgress()) {
        qWarning("trying to connect to phone while in progress");
        return;
    }
    if (m_bluetooth->isValid()) {
        foreach(QBluetoothAddress addr, m_bluetooth->connectedDevices()) {
            if (addr.toUInt64() == Settings::PhoneAddr) {
                changeState(ServiceDiscovery);
                connectToPhone(addr);
                return;
            }
        }
        changeState(DeviceDiscovery);
        discoverAndTryAgain();
    } else {
        changeState(Error);
        emitError(tr("Local bluetooth device not found"));
    }
}

void PhoneCommunication::connectToPhone(const QBluetoothAddress & addr)
{
    m_serviceDiscovery->setRemoteAddress(addr);
    m_serviceDiscovery->start();
}

void PhoneCommunication::svcDiscoveryDone()
{
    if (m_serviceDiscovery->error() != QBluetoothServiceDiscoveryAgent::NoError) {
        changeState(Error);
        emitError(m_serviceDiscovery->errorString());
        return;
    }

    foreach(QBluetoothServiceInfo info, m_serviceDiscovery->discoveredServices()) {
        if (info.serviceName() == "Phonebook") {
            qDebug("found service Phonebook");
            changeState(SocketConnect);
            m_socket->connectToService(info);
            return;
        }
    }

    changeState(Error);
    emitError(tr("Sensors assistant service not found"));
}

void PhoneCommunication::devDiscoveryDone()
{
    qDebug() << "devDiscoveryDone";
    if (m_deviceDiscovery->error() != QBluetoothDeviceDiscoveryAgent::NoError) {
        changeState(Error);
        emitError(m_deviceDiscovery->errorString());
        return;
    }
    foreach(QBluetoothDeviceInfo info, m_deviceDiscovery->discoveredDevices()) {
        if (info.address().toUInt64() == Settings::PhoneAddr) {
            changeState(Pairing);
            //connectToPhone(info.address());
            m_bluetooth->requestPairing(info.address(), QBluetoothLocalDevice::Paired);
            return;
        }
    }
    changeState(Error);
    emitError(tr("Phone not found. Make sure it is enabled and discoverable"));
}

void PhoneCommunication::showDiscoveredDevice(const QBluetoothDeviceInfo & info)
{
    if (!info.address().isNull()) {
        qDebug() << "device discovered:" << info.name() << info.address();
    }
}

void PhoneCommunication::showDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error err)
{
    qWarning() << "device discovery error: " << err;
}

void PhoneCommunication::processPairingFinished(const QBluetoothAddress & addr, QBluetoothLocalDevice::Pairing pairing)
{
    qDebug() << "pairing finished: " << addr << pairing;
    foreach(QBluetoothAddress addr, m_bluetooth->connectedDevices()) {
        if (addr.toUInt64() == Settings::PhoneAddr) {
            changeState(ServiceDiscovery);
            connectToPhone(addr);
            return;
        }
    }
    changeState(Error);
    emitError(tr("After successfull pairing the phone is not found"));
}

void PhoneCommunication::serviceConnected()
{
    changeState(Connected);
    emitConnected();
}

void PhoneCommunication::serviceError(QBluetoothSocket::SocketError)
{
    QString err = m_socket->errorString();
    m_socket->close();
    changeState(Error);
    emitError(err);
}

void PhoneCommunication::emitError(const QString & err) {
    qWarning() << err;
    m_active = false;
    emit error(err);
}

void PhoneCommunication::emitConnected() {
    m_active = false;
    emit connected();
}

void PhoneCommunication::changeState(State state)
{
    qDebug() << "change state to: " << stateToString(state);
    m_state = state;
    emit stateChanged(m_state);
}

bool PhoneCommunication::inProgress() const
{
    return m_state != Initial && m_state != Connected && m_state != Error;
}

void PhoneCommunication::discoverAndTryAgain()
{
    m_deviceDiscovery->start();
}

QString PhoneCommunication::stateToString(State state) const
{
    switch (state) {
    case Initial:
        return "Initial";
    case DeviceDiscovery:
        return "DeviceDiscovery";
    case Pairing:
        return "Pairing";
    case ServiceDiscovery:
        return "ServiceDiscovery";
    case SocketConnect:
        return "SocketConnect";
    case Error:
        return "Error";
    case Connected:
        return "Connected";
    default:
        return "UNKNOWN";
    }
}
