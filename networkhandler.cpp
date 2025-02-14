#include "networkhandler.h"
#include <QHostAddress>
#include <QDebug>

NetworkHandler* NetworkHandler::m_instance = nullptr;

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &NetworkHandler::handleResponse);
}

NetworkHandler::~NetworkHandler()
{
    m_udpSocket->close();
    delete m_udpSocket;
}

NetworkHandler* NetworkHandler::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new NetworkHandler();
    }
    return m_instance;
}

void NetworkHandler::registerDevice(Device* device)
{
    m_devices.append(device);
    connect(device, &Device::sendCommandSignal,
            this, &NetworkHandler::sendCommandToDevice);
}

void NetworkHandler::unregisterDevice(Device *device)
{
    m_devices.removeOne(device);
}

void NetworkHandler::sendCommandToDevice(const QByteArray& command, const QHostAddress& ip)
{
    // Wysyłamy komendę do localhost (127.0.0.1), ale zachowujemy IP urządzenia
    QHostAddress localAddress("127.0.0.1");

    m_udpSocket->writeDatagram(command, localAddress, PORT);
    qDebug() << "Command sent to localhost (127.0.0.1):" << command;
    qDebug() << "Original Device IP:" << ip.toString();
}


void NetworkHandler::handleResponse()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress senderIP;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                  &senderIP, &senderPort);

        for (auto device : m_devices) {
            if (device->getDeviceIP() == senderIP) {
                device->handleResponse(datagram);
                break;
            }
        }
    }
}

QList<Device*> NetworkHandler::getDevices()
{
    return m_devices;
}
