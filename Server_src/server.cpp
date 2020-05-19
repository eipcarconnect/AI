#include "server.h"
#include <iostream>
#include <fstream>

#include <QJsonObject>
#include <QJsonDocument>

Server::Server(QObject *parent) : QObject(parent), websocket(new QWebSocketServer(QStringLiteral("AI server progression"), QWebSocketServer::NonSecureMode)), tcp(new QTcpServer)
{
    websocket->listen(QHostAddress::Any, 4344);
    tcp->listen(QHostAddress::Any, 4343);

    /// On new client connection

    connect(websocket.data(), &QWebSocketServer::newConnection, [this](){
        auto websock = this->websocket->nextPendingConnection();
        webClients.push_back(websock);
        connect(websock, &QWebSocket::textMessageReceived, [this](const QString &message){
            auto msg = message.toStdString();
            std::cout << "Received from WEB CLIENT: " << msg << std::endl;

            if (msg == "save_ann") {
                for (auto &web : trainingServers)
                    web->write(QString("save_ann").toUtf8());
            }
        });

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
    });


    /// On new training server connection

    connect(tcp.data(), &QTcpServer::newConnection, [this](){
        auto trainingAI = this->tcp->nextPendingConnection();
        trainingServers.push_back(trainingAI);
        connect(trainingAI, &QTcpSocket::readyRead, [this, trainingAI](){
            auto buffer = trainingAI->readAll();
            std::cout << "BONSOIR: " << QString(buffer).toStdString().size() << " " << QString(buffer).toStdString() << std::endl;
            //TrainingNetMessage *message = (TrainingNetMessage*)buffer.data();
            Stat *message = (Stat*)buffer.data();

            //if (message->type == "stat") {
            /*trainingStats.push_back(message->stat);
            QJsonObject json;
            json.insert("max", message->stat.max);
            json.insert("min", message->stat.min);
            json.insert("moy", message->stat.moy);*/
            trainingStats.push_back(*message);
            QJsonObject json;
            json.insert("max", message->max);
            json.insert("min", message->min);
            json.insert("moy", message->moy);
                QJsonDocument doc(json);
                QString strJson(doc.toJson(QJsonDocument::Compact));

                for (auto &web : webClients)
                    web->sendTextMessage(strJson);
            /*}
            else if (message->type == "save") {
                std::cout << "Saving new file: " << message->save.name << std::endl;
                std::ofstream outfile(message->save.name);
                outfile << message->save.file;
                outfile.close();
            }*/
        });
        std::cout << "new training ai" << std::endl;
    });
}
