#ifndef GENERATION_H
#define GENERATION_H

#include <QObject>
#include <QTcpSocket>
#include "src/NeuralNetwork.hpp"

class Generation : QObject
{
    Q_OBJECT
public:
    Generation(QTcpSocket *tcp, std::string name);

    void createGenaration(int size = 1000);
    void loadData(std::string path);

private:
    std::string name;
    std::list<std::shared_ptr<NeuralNetwork>> generation;
};

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

#endif // GENERATION_H
