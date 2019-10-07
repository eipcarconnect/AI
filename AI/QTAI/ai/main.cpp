#include <QCoreApplication>

#include <QTcpSocket>
#include <QHostAddress>

struct type{
    type(int max, int min, int moy): max(max), min(min), moy(moy) {}
    int max;
    int min;
    int moy;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost(QHostAddress(QHostAddress::LocalHost), 4343);

    type tmp(100, 55, 75);

    socket.write((const char*) &tmp, sizeof(type));

    return a.exec();
}
