#include "networkhandler.h"
#include <qdebug.h>

NetworkHandler* NetworkHandler::m_instance = nullptr;

NetworkHandler::NetworkHandler(QObject *parent)
:QObject(parent)
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
    if(m_instance == nullptr) {
       m_instance = new NetworkHandler();
    }
    return m_instance;
}
void NetworkHandler::registerDevice(Device* device, const QHostAddress &address)
{
    m_devices.append(device);
    connect(device, &Device::sendCommandSignal,
            this, &NetworkHandler::sendCommandToDevice);
}
void NetworkHandler::sendCommandToDevice(const QByteArray& command, const QHostAddress& ip)
{
    m_udpSocket->writeDatagram(command, ip, PORT);
    //eventually qDebug() << "Command sent to " << ip.toString(); etc
    qDebug() << "Command sent to " << ip.toString();
    qDebug() << "Command:" << command;
}

void NetworkHandler::handleResponse()
{
    while(m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress senderIP;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                  &senderIP, &senderPort);

        for(auto device : m_devices) {
            if(device->getDeviceIP() == senderIP) {
                device->handleResponse(datagram);
            break;
            }
        }
    }
}
