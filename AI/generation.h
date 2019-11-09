#ifndef GENERATION_H
#define GENERATION_H

#include <QObject>
#include <QTcpSocket>
#include "src/NeuralNetwork.hpp"

class Generation : QObject
{
    Q_OBJECT
public:
    Generation(QTcpSocket *tcp);

    void createGenaration(int size = 1000);
    void loadData(std::string path);

private:
    std::list<std::shared_ptr<NeuralNetwork>> generation;
};

struct Stat{
    Stat(double min, double max, double moy): max(max), min(min), moy(moy) {}
    double max;
    double min;
    double moy;
};

#endif // GENERATION_H
