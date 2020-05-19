#ifndef GENERATION_H
#define GENERATION_H

#include <QObject>
#include <QTcpSocket>
#include <QtCore/QObjectCleanupHandler>
#include "src/NeuralNetwork.hpp"
#include "../InputGen_src/InputGeneration.hpp"

class Generation : public QObject
{
    Q_OBJECT
public:
    Generation(QObject *parent = 0): QObject(parent) {};
    Generation(QTcpSocket *tcp, std::string name);
    virtual ~Generation() {};

    void createGenaration(int size = 1000);
    void loadData(std::string path);

private:
    std::string name;
    int size = 0;
    std::list<std::shared_ptr<NeuralNetwork>> generation;
};

struct Stat{
    Stat(double max, double min, double moy): max(max), min(min), moy(moy) {}
    double max;
    double min;
    double moy;
};

struct Save {
    Save(std::string name, std::string file): sizeName(name.size()), sizeFile(file.size()), name(name), file(file) {}
    int sizeName;
    int sizeFile;
    std::string name;
    std::string file;
};

enum class MessageType {
    Stat,
    Save
};

struct TrainingNetMessage {
    TrainingNetMessage(MessageType type, double max, double min, double moy): type(type), stat(max, min, moy), save("", "") {}
    TrainingNetMessage(MessageType type, std::string name, std::string file): type(type), stat(0, 0, 0), save(name, file) {}

    MessageType type;
    Stat stat;
    Save save;
};

#endif // GENERATION_H
