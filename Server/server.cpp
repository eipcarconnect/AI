#include "server.h"
#include <iostream>

#include <QJsonObject>
#include <QJsonDocument>

Server::Server(QObject *parent) : QObject(parent), websocket(new QWebSocketServer(QStringLiteral("AI server progression"), QWebSocketServer::NonSecureMode)), tcp(new QTcpServer)
{
    websocket->listen(QHostAddress::Any, 4344);
    tcp->listen(QHostAddress::Any, 4343);

    connect(websocket.data(), &QWebSocketServer::newConnection, [this](){
        auto websock = this->websocket->nextPendingConnection();
        webClients.push_back(QSharedPointer<QWebSocket>(websock));

        for (auto stat : trainingStats) {
            QJsonObject json;
            json.insert("max", stat.max);
            json.insert("min", stat.min);
            json.insert("moy", stat.moy);
            QJsonDocument doc(json);
            QString strJson(doc.toJson(QJsonDocument::Compact));

            websock->sendTextMessage(strJson);
        }
        std::cout << "new web client" << std::endl;
        //startTimer(1000);
    });

    connect(tcp.data(), &QTcpServer::newConnection, [this](){
        auto trainingAI = this->tcp->nextPendingConnection();
        connect(trainingAI, &QTcpSocket::readyRead, [this, trainingAI](){
            auto buffer = trainingAI->readAll();
            Stat *stat = (Stat*)buffer.data();
            trainingStats.push_back(*stat);

            QJsonObject json;
            json.insert("max", stat->max);
            json.insert("min", stat->min);
            json.insert("moy", stat->moy);
            QJsonDocument doc(json);
            QString strJson(doc.toJson(QJsonDocument::Compact));

            for (auto &web : webClients)
                web->sendTextMessage(strJson);
            std::cout << stat->max << " " << stat->min << " " << stat->moy << std::endl;
        });
        std::cout << "new training ai" << std::endl;
    });
}

void Server::timerEvent(QTimerEvent *)
{
	static int moy = 100;
    static int i = 0;
    QJsonObject json;

    json.insert("label", i);
    ++i;
    int max = rand() % 100 + moy;
    int min = moy - (rand() % 100);
    int nbmin = rand() % 8 + 1;
    int nbmax = rand() % 10 + 1;
    int moye = (min * nbmin + max * nbmax) / (nbmin + nbmax) ;
    moy = moye;
    json.insert("max", max);
    json.insert("min", min);
    json.insert("moy", moye);

    QJsonDocument doc(json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    for(auto webclient : webClients) {
        webclient->sendTextMessage(doc.toJson(QJsonDocument::Compact));
        std::cout << moye <<' ' << max<< ' ' << min << std::endl;
    }
}
