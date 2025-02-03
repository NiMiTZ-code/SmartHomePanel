#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QUdpSocket>
#include <QMap>

#include "device.h"

class NetworkHandler: public QObject
{
    Q_OBJECT
private:
    QUdpSocket *m_udpSocket;
    static NetworkHandler* m_instance;
    static const int TIMEOUT_MS = 2000;
    static const quint16 PORT = 7777;

public:
    explicit NetworkHandler(QObject *parent = nullptr);
    ~NetworkHandler();

    void registerDevice(Device* device, const QHostAddress &address);
    static NetworkHandler* getInstance(); //singletgon

public slots:
    void sendCommandToDevice(const QByteArray& command, const QHostAddress& ip);
    void handleResponse();

signals:
};

#endif // NETWORKHANDLER_H
