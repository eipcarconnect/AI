#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QSharedPointer>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void timerEvent(QTimerEvent *) override;

signals:

public slots:

private:
    QSharedPointer<QWebSocketServer>    websocket;
    QSharedPointer<QTcpServer>          tcp;

    QList<QSharedPointer<QWebSocket>>   webClients;
};

#endif // SERVER_H
