#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QSharedPointer>


struct Stat{
    Stat(double max, double min, double moy): max(max), min(min), moy(moy) {}
    double max;
    double min;
    double moy;
};

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void timerEvent(QTimerEvent *) override;

signals:

public slots:

private:
    std::list<Stat>                     trainingStats;

    QSharedPointer<QWebSocketServer>    websocket;
    QSharedPointer<QTcpServer>          tcp;

    QList<QSharedPointer<QWebSocket>>   webClients;
};

#endif // SERVER_H
