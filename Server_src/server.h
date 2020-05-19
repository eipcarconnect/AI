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

struct Save {
    Save(std::string name, std::string file): name(name), file(file) {}
    std::string name;
    std::string file;
};

struct TrainingNetMessage {
    TrainingNetMessage(std::string type, double max, double min, double moy): type(type), stat(max, min, moy), save("", "") {}
    TrainingNetMessage(std::string type, std::string name, std::string file): type(type), stat(0, 0, 0), save(name, file) {}
    std::string type;
    //union {
        Stat stat;
        Save save;
    //};
};

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

public slots:

private:
    std::list<Stat>                     trainingStats;

    QSharedPointer<QWebSocketServer>    websocket;
    QSharedPointer<QTcpServer>          tcp;

    QList<QWebSocket*>   webClients;
    QList<QTcpSocket*>   trainingServers;
};

#endif // SERVER_H
