#include "server.h"
#include <iostream>

#include <QJsonObject>
#include <QJsonDocument>

Server::Server(QObject *parent) : QObject(parent), websocket(new QWebSocketServer(QStringLiteral("AI server progression"), QWebSocketServer::NonSecureMode)), tcp(new QTcpServer)
{
    websocket->listen(QHostAddress::Any, 4344);
    tcp->listen(QHostAddress::Any, 4343);

    connect(websocket.data(), &QWebSocketServer::newConnection, [this](){
        webClients.push_back(QSharedPointer<QWebSocket>(this->websocket->nextPendingConnection()));
        std::cout << "nouvel web client" << std::endl;
        startTimer(1000);
    });

    connect(tcp.data(), &QTcpServer::newConnection, [this](){
        this->tcp->nextPendingConnection();
        std::cout << "nouveau training ai";
    });
}

void Server::timerEvent(QTimerEvent *)
{
    static int i = 0;
    QJsonObject json;

    json.insert("label", i);
    ++i;
    int tmp = rand();
    json.insert("data", tmp);

    QJsonDocument doc(json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    for(auto webclient : webClients) {
        webclient->sendTextMessage(doc.toJson(QJsonDocument::Compact));
        std::cout << tmp << std::endl;
    }
}
